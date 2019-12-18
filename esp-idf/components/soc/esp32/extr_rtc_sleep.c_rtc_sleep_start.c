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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ GET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_GET_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_BIAS_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DBG_ATTEN ; 
 int /*<<< orphan*/  RTC_CNTL_DBG_ATTEN_DEFAULT ; 
 int /*<<< orphan*/  RTC_CNTL_INT_CLR_REG ; 
 int /*<<< orphan*/  RTC_CNTL_INT_RAW_REG ; 
 int RTC_CNTL_SLEEP_EN ; 
 int /*<<< orphan*/  RTC_CNTL_SLP_REJECT_CONF_REG ; 
 int RTC_CNTL_SLP_REJECT_INT_CLR ; 
 int RTC_CNTL_SLP_REJECT_INT_RAW ; 
 int RTC_CNTL_SLP_WAKEUP_INT_CLR ; 
 int RTC_CNTL_SLP_WAKEUP_INT_RAW ; 
 int /*<<< orphan*/  RTC_CNTL_STATE0_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WAKEUP_ENA ; 
 int /*<<< orphan*/  RTC_CNTL_WAKEUP_STATE_REG ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t rtc_sleep_start(uint32_t wakeup_opt, uint32_t reject_opt)
{
    REG_SET_FIELD(RTC_CNTL_WAKEUP_STATE_REG, RTC_CNTL_WAKEUP_ENA, wakeup_opt);
    WRITE_PERI_REG(RTC_CNTL_SLP_REJECT_CONF_REG, reject_opt);

    /* Start entry into sleep mode */
    SET_PERI_REG_MASK(RTC_CNTL_STATE0_REG, RTC_CNTL_SLEEP_EN);

    while (GET_PERI_REG_MASK(RTC_CNTL_INT_RAW_REG,
            RTC_CNTL_SLP_REJECT_INT_RAW | RTC_CNTL_SLP_WAKEUP_INT_RAW) == 0) {
        ;
    }
    /* In deep sleep mode, we never get here */
    uint32_t reject = REG_GET_FIELD(RTC_CNTL_INT_RAW_REG, RTC_CNTL_SLP_REJECT_INT_RAW);
    SET_PERI_REG_MASK(RTC_CNTL_INT_CLR_REG,
            RTC_CNTL_SLP_REJECT_INT_CLR | RTC_CNTL_SLP_WAKEUP_INT_CLR);

    /* restore DBG_ATTEN to the default value */
    REG_SET_FIELD(RTC_CNTL_BIAS_CONF_REG, RTC_CNTL_DBG_ATTEN, RTC_CNTL_DBG_ATTEN_DEFAULT);
    return reject;
}