#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ portBASE_TYPE ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  TickType_t ;
struct TYPE_2__ {int /*<<< orphan*/  ret_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_1__ context ; 
 scalar_t__ pdTRUE ; 
 scalar_t__ xQueueReceive (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 

esp_err_t sdio_slave_send_get_finished(void** out_arg, TickType_t wait)
{
    void* arg = NULL;
    portBASE_TYPE err = xQueueReceive(context.ret_queue, &arg, wait);
    if (out_arg) *out_arg = arg;
    if (err != pdTRUE) return ESP_ERR_TIMEOUT;
    return ESP_OK;
}