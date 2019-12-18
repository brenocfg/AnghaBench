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
typedef  int touch_pad_intr_mask_t ;
typedef  int /*<<< orphan*/ * intr_handler_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int RTC_CNTL_TOUCH_DONE_INT_ENA_S ; 
 int TOUCH_PAD_INTR_MASK_ALL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_isr_register (int /*<<< orphan*/ *,void*,int) ; 

esp_err_t touch_pad_isr_register(intr_handler_t fn, void *arg, touch_pad_intr_mask_t intr_mask)
{
    assert(fn != NULL);
    return rtc_isr_register(fn, arg, TOUCH_PAD_INTR_MASK_ALL & (intr_mask << RTC_CNTL_TOUCH_DONE_INT_ENA_S));
}