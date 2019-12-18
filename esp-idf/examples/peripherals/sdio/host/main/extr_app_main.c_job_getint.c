#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  esp_slave_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  JOB_SEND_INT ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  slave_inform_job (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void job_getint(esp_slave_context_t *context)
{
    ESP_LOGI(TAG, "========JOB: get interrupts from slave========");
    slave_inform_job(context, JOB_SEND_INT);
}