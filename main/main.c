#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char* TAG = "ALERT";
#define LED GPIO_NUM_4

TaskHandle_t myTaskHandle = NULL;

void blink_led_task (void * pvParameters) {
    int count = 0;
	for (;;) {
        count++;
	    gpio_reset_pin(LED);
	    /* Set the GPIO as a push/pull output */
	    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
	    while (true) {
	    	gpio_set_level(LED, 1);
	    	vTaskDelay(1000 / portTICK_PERIOD_MS);
	    	gpio_set_level(LED, 0);
	    	vTaskDelay(1000 / portTICK_PERIOD_MS);
	    	ESP_LOGI(TAG,"Task Working");

	    }
	}
}

void app_main(void)
{
 xTaskCreate(blink_led_task, "led_blink", 4096, NULL, 10, &myTaskHandle);
}
