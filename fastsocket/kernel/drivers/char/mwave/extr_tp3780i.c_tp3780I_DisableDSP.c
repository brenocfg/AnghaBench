#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* bInterruptClaimed; int /*<<< orphan*/  usDspIrq; } ;
struct TYPE_5__ {void* bDSPEnabled; TYPE_2__ rDspSettings; } ;
typedef  TYPE_1__ THINKPAD_BD_DATA ;
typedef  TYPE_2__ DSP_3780I_CONFIG_SETTINGS ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  PRINTK_2 (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TRACE_TP3780I ; 
 int /*<<< orphan*/  dsp3780I_DisableDSP (TYPE_2__*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smapi_set_DSP_power_state (void*) ; 

int tp3780I_DisableDSP(THINKPAD_BD_DATA * pBDData)
{
	int retval = 0;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_DisableDSP entry pBDData %p\n", pBDData);

	if (pBDData->bDSPEnabled) {
		dsp3780I_DisableDSP(&pBDData->rDspSettings);
		if (pSettings->bInterruptClaimed) {
			free_irq(pSettings->usDspIrq, NULL);
			pSettings->bInterruptClaimed = FALSE;
		}
		smapi_set_DSP_power_state(FALSE);
		pBDData->bDSPEnabled = FALSE;
	}

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_DisableDSP exit retval %x\n", retval);

	return retval;
}