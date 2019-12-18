#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_6__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_10__ {TYPE_4__* s_ModuleInfo; TYPE_1__ s_BoardInfos; } ;
struct TYPE_8__ {TYPE_2__* s_82X54TimerInfo; } ;
struct TYPE_9__ {TYPE_3__ s_82X54ModuleInfo; } ;
struct TYPE_7__ {int b_82X54Init; unsigned int b_OutputLevel; } ;

/* Variables and functions */
 int APCI1710_82X54_TIMER ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_5__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

int i_APCI1710_GetTimerOutputLevel(struct comedi_device *dev,
				   unsigned char b_ModulNbr, unsigned char b_TimerNbr,
				   unsigned char *pb_OutputLevel)
{
	int i_ReturnValue = 0;
	unsigned int dw_TimerStatus;

	/* Test the module number */
	if (b_ModulNbr < 4) {
		/* Test if 82X54 timer */
		if ((devpriv->s_BoardInfos.dw_MolduleConfiguration[b_ModulNbr] & 0xFFFF0000UL) == APCI1710_82X54_TIMER) {
			/* Test the timer number */
			if (b_TimerNbr <= 2) {
				/* Test if timer initialised */
				if (devpriv->s_ModuleInfo[b_ModulNbr].s_82X54ModuleInfo.s_82X54TimerInfo[b_TimerNbr].b_82X54Init == 1) {
					/* Latch the timer value */
					outl((2 << b_TimerNbr) | 0xE0, devpriv->s_BoardInfos.ui_Address + 12 + (64 * b_ModulNbr));

					/* Read the timer status */
					dw_TimerStatus = inl(devpriv->s_BoardInfos.ui_Address + 16 + (b_TimerNbr * 4) + (64 * b_ModulNbr));

					*pb_OutputLevel = (unsigned char) (((dw_TimerStatus >> 7) & 1) ^ devpriv-> s_ModuleInfo[b_ModulNbr].s_82X54ModuleInfo.s_82X54TimerInfo[b_TimerNbr].b_OutputLevel);
				} else {
					/* Timer not initialised see function */
					DPRINTK("Timer not initialised see function\n");
					i_ReturnValue = -5;
				}
			} else {
				/* Timer selection wrong */
				DPRINTK("Timer selection wrong\n");
				i_ReturnValue = -3;
			}	/*  if ((b_TimerNbr >= 0) && (b_TimerNbr <= 2)) */
		} else {
			/* The module is not a TIMER module */
			DPRINTK("The module is not a TIMER module\n");
			i_ReturnValue = -4;
		}
	} else {
		/* Module number error */
		DPRINTK("Module number error\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}