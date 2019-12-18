#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int s32 ;
struct TYPE_2__ {int data_fmt; } ;

/* Variables and functions */
 int WPAD_CHAN_0 ; 
 int WPAD_CHAN_ALL ; 
 int WPAD_ERR_BADVALUE ; 
 int WPAD_ERR_BAD_CHANNEL ; 
 int WPAD_ERR_NONE ; 
 int WPAD_ERR_NOT_READY ; 
#define  WPAD_FMT_BTNS 130 
#define  WPAD_FMT_BTNS_ACC 129 
#define  WPAD_FMT_BTNS_ACC_IR 128 
 int WPAD_MAX_WIIMOTES ; 
 scalar_t__ WPAD_STATE_DISABLED ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wpad_setfmt (int) ; 
 int /*<<< orphan*/ ** __wpads ; 
 scalar_t__ __wpads_inited ; 
 TYPE_1__* __wpdcb ; 

s32 WPAD_SetDataFormat(s32 chan, s32 fmt)
{
	u32 level;
	s32 ret;
	int i;

	if(chan == WPAD_CHAN_ALL) {
		for(i=WPAD_CHAN_0; i<WPAD_MAX_WIIMOTES; i++)
			if((ret = WPAD_SetDataFormat(i, fmt)) < WPAD_ERR_NONE)
				return ret;
		return WPAD_ERR_NONE;
	}

	if(chan<WPAD_CHAN_0 || chan>=WPAD_MAX_WIIMOTES) return WPAD_ERR_BAD_CHANNEL;

	_CPU_ISR_Disable(level);
	if(__wpads_inited==WPAD_STATE_DISABLED) {
		_CPU_ISR_Restore(level);
		return WPAD_ERR_NOT_READY;
	}

	if(__wpads[chan]!=NULL) {
		switch(fmt) {
			case WPAD_FMT_BTNS:
			case WPAD_FMT_BTNS_ACC:
			case WPAD_FMT_BTNS_ACC_IR:
				__wpdcb[chan].data_fmt = fmt;
				__wpad_setfmt(chan);
				break;
			default:
				_CPU_ISR_Restore(level);
				return WPAD_ERR_BADVALUE;
		}
	}
	_CPU_ISR_Restore(level);
	return WPAD_ERR_NONE;
}