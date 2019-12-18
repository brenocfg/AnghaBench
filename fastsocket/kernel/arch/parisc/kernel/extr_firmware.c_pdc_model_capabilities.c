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

/* Variables and functions */
 int /*<<< orphan*/  PDC_MODEL ; 
 int /*<<< orphan*/  PDC_MODEL_CAPABILITIES ; 
 unsigned long PDC_MODEL_OS32 ; 
 int PDC_OK ; 
 int /*<<< orphan*/  __pa (unsigned long*) ; 
 int /*<<< orphan*/  convert_to_wide (unsigned long*) ; 
 int mem_pdc_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_lock ; 
 unsigned long* pdc_result ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pdc_model_capabilities(unsigned long *capabilities)
{
        int retval;
	unsigned long flags;

        spin_lock_irqsave(&pdc_lock, flags);
        pdc_result[0] = 0; /* preset zero (call may not be implemented!) */
        retval = mem_pdc_call(PDC_MODEL, PDC_MODEL_CAPABILITIES, __pa(pdc_result), 0);
        convert_to_wide(pdc_result);
        if (retval == PDC_OK) {
                *capabilities = pdc_result[0];
        } else {
                *capabilities = PDC_MODEL_OS32;
        }
        spin_unlock_irqrestore(&pdc_lock, flags);

        return retval;
}