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
typedef  int /*<<< orphan*/  example_job_t ;
typedef  int /*<<< orphan*/  esp_slave_context_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLAVE_INTR_NOTIFY ; 
 int /*<<< orphan*/  SLAVE_REG_JOB ; 
 int /*<<< orphan*/  esp_slave_send_slave_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_slave_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline esp_err_t slave_inform_job(esp_slave_context_t *context, example_job_t job)
{
    esp_err_t ret;
    ret = esp_slave_write_reg(context, SLAVE_REG_JOB, job, NULL);
    ESP_ERROR_CHECK(ret);
    ret = esp_slave_send_slave_intr(context, BIT(SLAVE_INTR_NOTIFY));
    ESP_ERROR_CHECK(ret);
    return ret;
}