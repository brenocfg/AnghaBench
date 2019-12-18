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
struct TYPE_5__ {int type; } ;
struct TYPE_6__ {TYPE_1__ exp; } ;
typedef  TYPE_2__ wiimote ;
typedef  int u32 ;
typedef  size_t s32 ;

/* Variables and functions */
 scalar_t__ WIIMOTE_IS_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_CONNECTED ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP ; 
 int /*<<< orphan*/  WIIMOTE_STATE_HANDSHAKE_COMPLETE ; 
 size_t WPAD_ERR_NONE ; 
 size_t WPAD_ERR_NOT_READY ; 
 size_t WPAD_ERR_NO_CONTROLLER ; 
#define  WPAD_EXP_CLASSIC 129 
 int WPAD_EXP_NONE ; 
#define  WPAD_EXP_NUNCHUK 128 
 scalar_t__ WPAD_STATE_DISABLED ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 TYPE_2__** __wpads ; 
 scalar_t__ __wpads_inited ; 

s32 WPAD_Probe(s32 chan,u32 *type)
{
	s32 ret;
	u32 level,dev;
	wiimote *wm = NULL;

	//if(chan<WPAD_CHAN_0 || chan>=WPAD_MAX_WIIMOTES) return WPAD_ERR_BAD_CHANNEL;

	_CPU_ISR_Disable(level);
	if(__wpads_inited==WPAD_STATE_DISABLED) {
		_CPU_ISR_Restore(level);
		return WPAD_ERR_NOT_READY;
	}

	wm = __wpads[chan];
	if(wm && WIIMOTE_IS_SET(wm,WIIMOTE_STATE_CONNECTED)) {
		if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_HANDSHAKE_COMPLETE)) {
			dev = WPAD_EXP_NONE;
			if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP)) {
				switch(wm->exp.type) {
					case WPAD_EXP_NUNCHUK:
					case WPAD_EXP_CLASSIC:
						dev = wm->exp.type;
						break;
				}
			}
			if(type!=NULL) *type = dev;
			ret = WPAD_ERR_NONE;
		} else
			ret = WPAD_ERR_NOT_READY;
	} else
		ret = WPAD_ERR_NO_CONTROLLER;
	_CPU_ISR_Restore(level);

	return ret;
}