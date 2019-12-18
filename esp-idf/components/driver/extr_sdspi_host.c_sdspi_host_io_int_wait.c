#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  gpio_int; int /*<<< orphan*/  semphr_int; } ;
typedef  TYPE_1__ slot_info_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  TickType_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ gpio_get_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_intr_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_intr_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ pdFALSE ; 
 TYPE_1__* s_slots ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t sdspi_host_io_int_wait(int slot, TickType_t timeout_ticks)
{
    slot_info_t* pslot = &s_slots[slot];
    //skip the interrupt and semaphore if the gpio is already low.
    if (gpio_get_level(pslot->gpio_int)==0) return ESP_OK;

    //clear the semaphore before wait
    xSemaphoreTake(pslot->semphr_int, 0);
    //enable the interrupt and wait for the semaphore
    gpio_intr_enable(pslot->gpio_int);
    BaseType_t ret = xSemaphoreTake(pslot->semphr_int, timeout_ticks);
    if (ret == pdFALSE) {
        gpio_intr_disable(pslot->gpio_int);
        return ESP_ERR_TIMEOUT;
    }
    return ESP_OK;
}