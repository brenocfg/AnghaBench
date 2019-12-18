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
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  intr_handle; int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EXIT_CRIT_RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TIMERG0 ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_protect (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* twdt_config ; 
 int /*<<< orphan*/  twdt_spinlock ; 

esp_err_t esp_task_wdt_deinit(void)
{
    portENTER_CRITICAL(&twdt_spinlock);
    //TWDT must already be initialized
    ASSERT_EXIT_CRIT_RETURN((twdt_config != NULL), ESP_ERR_NOT_FOUND);
    //Task list must be empty
    ASSERT_EXIT_CRIT_RETURN((twdt_config->list == NULL), ESP_ERR_INVALID_STATE);

    //Disable hardware timer
    timer_ll_wdt_set_protect(&TIMERG0, false);   //Disable write protection
    timer_ll_wdt_set_enable(&TIMERG0, false);                   //Disable timer
    timer_ll_wdt_set_protect(&TIMERG0, true);                     //Enable write protection

    ESP_ERROR_CHECK(esp_intr_free(twdt_config->intr_handle));  //Unregister interrupt
    free(twdt_config);                      //Free twdt_config
    twdt_config = NULL;
    portEXIT_CRITICAL(&twdt_spinlock);
    return ESP_OK;
}