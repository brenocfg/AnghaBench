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
struct TYPE_6__ {unsigned short usDspBaseIO; } ;
struct TYPE_5__ {int ClockControl; scalar_t__ Reserved; int /*<<< orphan*/  ConfigMode; int /*<<< orphan*/  SoftReset; } ;
typedef  TYPE_1__ DSP_ISA_SLAVE_CONTROL ;
typedef  TYPE_2__ DSP_3780I_CONFIG_SETTINGS ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_IsaSlaveControl ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MKWORD (TYPE_1__) ; 
 int /*<<< orphan*/  OutWordDsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINTK_1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE_3780I ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dsp_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

int dsp3780I_DisableDSP(DSP_3780I_CONFIG_SETTINGS * pSettings)
{
	unsigned long flags;
	unsigned short usDspBaseIO = pSettings->usDspBaseIO;
	DSP_ISA_SLAVE_CONTROL rSlaveControl;


	PRINTK_1(TRACE_3780I, "3780i::dsp3780i_DisableDSP entry\n");

	rSlaveControl.ClockControl = 0;
	rSlaveControl.SoftReset = TRUE;
	rSlaveControl.ConfigMode = FALSE;
	rSlaveControl.Reserved = 0;
	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_IsaSlaveControl, MKWORD(rSlaveControl));

	udelay(5);

	rSlaveControl.ClockControl = 1;
	OutWordDsp(DSP_IsaSlaveControl, MKWORD(rSlaveControl));
	spin_unlock_irqrestore(&dsp_lock, flags);

	udelay(5);


	PRINTK_1(TRACE_3780I, "3780i::dsp3780i_DisableDSP exit\n");

	return 0;
}