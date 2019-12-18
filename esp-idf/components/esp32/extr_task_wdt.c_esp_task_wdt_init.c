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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  twdt_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int timeout; int panic; int /*<<< orphan*/  intr_handle; int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EXIT_CRIT_RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  ETS_TG0_WDT_LEVEL_INTR_SOURCE ; 
 int /*<<< orphan*/  PERIPH_TIMG0_MODULE ; 
 int TG0_WDT_TICK_US ; 
 int /*<<< orphan*/  TIMERG0 ; 
 int /*<<< orphan*/  TIMER_WDT_INT ; 
 int /*<<< orphan*/  TIMER_WDT_RESET_SYSTEM ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  esp_intr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_wdt_isr ; 
 int /*<<< orphan*/  timer_ll_wdt_feed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_ll_wdt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_protect (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_tick (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_timeout (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_timeout_behavior (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* twdt_config ; 
 int /*<<< orphan*/  twdt_spinlock ; 

esp_err_t esp_task_wdt_init(uint32_t timeout, bool panic)
{
    portENTER_CRITICAL(&twdt_spinlock);
    if(twdt_config == NULL){        //TWDT not initialized yet
        //Allocate memory for wdt_config
        twdt_config = calloc(1, sizeof(twdt_config_t));
        ASSERT_EXIT_CRIT_RETURN((twdt_config != NULL), ESP_ERR_NO_MEM);

        twdt_config->list = NULL;
        twdt_config->timeout = timeout;
        twdt_config->panic = panic;

        //Register Interrupt and ISR
        ESP_ERROR_CHECK(esp_intr_alloc(ETS_TG0_WDT_LEVEL_INTR_SOURCE, 0, task_wdt_isr, NULL, &twdt_config->intr_handle));

        //Configure hardware timer
        periph_module_enable(PERIPH_TIMG0_MODULE);
        timer_ll_wdt_set_protect(&TIMERG0, false);               //Disable write protection
        timer_ll_wdt_init(&TIMERG0);
        timer_ll_wdt_set_tick(&TIMERG0, TG0_WDT_TICK_US); //Prescaler: wdt counts in ticks of TG0_WDT_TICK_US
        //1st stage timeout: interrupt
        timer_ll_wdt_set_timeout_behavior(&TIMERG0, 0, TIMER_WDT_INT);
        timer_ll_wdt_set_timeout(&TIMERG0, 0, twdt_config->timeout*1000*1000/TG0_WDT_TICK_US);
        //2nd stage timeout: reset system
        timer_ll_wdt_set_timeout_behavior(&TIMERG0, 1, TIMER_WDT_RESET_SYSTEM);
        timer_ll_wdt_set_timeout(&TIMERG0, 1, 2*twdt_config->timeout*1000*1000/TG0_WDT_TICK_US);
        timer_ll_wdt_set_enable(&TIMERG0, true);
        timer_ll_wdt_feed(&TIMERG0);
        timer_ll_wdt_set_protect(&TIMERG0, true);                         //Enable write protection
    } else {      //twdt_config previously initialized
        //Reconfigure task wdt
        twdt_config->panic = panic;
        twdt_config->timeout = timeout;

        //Reconfigure hardware timer
        timer_ll_wdt_set_protect(&TIMERG0, false);   //Disable write protection
        timer_ll_wdt_set_enable(&TIMERG0, false);                   //Disable timer
        //Set timeout before interrupt
        timer_ll_wdt_set_timeout(&TIMERG0, 0, twdt_config->timeout*1000*1000/TG0_WDT_TICK_US);
        //Set timeout before reset
        timer_ll_wdt_set_timeout(&TIMERG0, 1, 2*twdt_config->timeout*1000*1000/TG0_WDT_TICK_US);
        timer_ll_wdt_set_enable(&TIMERG0, true);                   //Renable timer
        timer_ll_wdt_feed(&TIMERG0);                         //Reset timer
        timer_ll_wdt_set_protect(&TIMERG0, true);                     //Enable write protection
    }
    portEXIT_CRITICAL(&twdt_spinlock);
    return ESP_OK;
}