#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  twdt_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {int sys_reset_length; int cpu_reset_length; int level_int_en; int en; int /*<<< orphan*/  stg1; int /*<<< orphan*/  stg0; } ;
struct TYPE_6__ {int clk_prescale; } ;
struct TYPE_9__ {int wdt_config2; int wdt_config3; int wdt_feed; void* wdt_wprotect; TYPE_2__ wdt_config0; TYPE_1__ wdt_config1; } ;
struct TYPE_8__ {int timeout; int panic; int /*<<< orphan*/  intr_handle; int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EXIT_CRIT_RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  ETS_TG0_WDT_LEVEL_INTR_SOURCE ; 
 int /*<<< orphan*/  PERIPH_TIMG0_MODULE ; 
 TYPE_5__ TIMERG0 ; 
 int /*<<< orphan*/  TIMG_WDT_STG_SEL_INT ; 
 int /*<<< orphan*/  TIMG_WDT_STG_SEL_RESET_SYSTEM ; 
 void* TIMG_WDT_WKEY_VALUE ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  esp_intr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_wdt_isr ; 
 TYPE_3__* twdt_config ; 
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
        TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;               //Disable write protection
        TIMERG0.wdt_config0.sys_reset_length=7;                 //3.2uS
        TIMERG0.wdt_config0.cpu_reset_length=7;                 //3.2uS
        TIMERG0.wdt_config0.level_int_en=1;
        TIMERG0.wdt_config0.stg0=TIMG_WDT_STG_SEL_INT;          //1st stage timeout: interrupt
        TIMERG0.wdt_config0.stg1=TIMG_WDT_STG_SEL_RESET_SYSTEM; //2nd stage timeout: reset system
        TIMERG0.wdt_config1.clk_prescale=80*500;                //Prescaler: wdt counts in ticks of 0.5mS
        TIMERG0.wdt_config2=twdt_config->timeout*2000;      //Set timeout before interrupt
        TIMERG0.wdt_config3=twdt_config->timeout*4000;      //Set timeout before reset
        TIMERG0.wdt_config0.en=1;
        TIMERG0.wdt_feed=1;
        TIMERG0.wdt_wprotect=0;                         //Enable write protection

    }else{      //twdt_config previously initialized
        //Reconfigure task wdt
        twdt_config->panic = panic;
        twdt_config->timeout = timeout;

        //Reconfigure hardware timer
        TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;   //Disable write protection
        TIMERG0.wdt_config0.en=0;                   //Disable timer
        TIMERG0.wdt_config2=twdt_config->timeout*2000;           //Set timeout before interrupt
        TIMERG0.wdt_config3=twdt_config->timeout*4000;           //Set timeout before reset
        TIMERG0.wdt_config0.en=1;                   //Renable timer
        TIMERG0.wdt_feed=1;                         //Reset timer
        TIMERG0.wdt_wprotect=0;                     //Enable write protection
    }
    portEXIT_CRITICAL(&twdt_spinlock);
    return ESP_OK;
}