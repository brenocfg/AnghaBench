#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct accel_t {int dummy; } ;
struct _wpad_cb {size_t queue_length; scalar_t__ queue_full; size_t queue_head; int /*<<< orphan*/  lstate; int /*<<< orphan*/ * queue_int; int /*<<< orphan*/ * queue_ext; } ;
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  WPADData ;
struct TYPE_4__ {struct accel_t accel_calib; } ;

/* Variables and functions */
 size_t EVENTQUEUE_LENGTH ; 
 size_t WIIMOTE_IS_FLAG_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ WIIMOTE_IS_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_CONNECTED ; 
 int /*<<< orphan*/  WIIMOTE_STATE_HANDSHAKE_COMPLETE ; 
 int /*<<< orphan*/  WIIUSE_SMOOTHING ; 
 size_t WPAD_ERR_NOT_READY ; 
 size_t WPAD_ERR_NO_CONTROLLER ; 
 size_t WPAD_ERR_QUEUE_EMPTY ; 
 scalar_t__ WPAD_STATE_DISABLED ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (size_t) ; 
 int /*<<< orphan*/  __wpad_calc_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct accel_t*,size_t) ; 
 TYPE_1__** __wpads ; 
 scalar_t__ __wpads_inited ; 
 struct _wpad_cb* __wpdcb ; 

s32 WPAD_ReadEvent(s32 chan, WPADData *data)
{
	u32 level;
	u32 maxbufs,smoothed = 0;
	struct accel_t *accel_calib = NULL;
	struct _wpad_cb *wpdcb = NULL;
	WPADData *lstate = NULL,*wpadd = NULL;

	//if(chan<WPAD_CHAN_0 || chan>=WPAD_MAX_WIIMOTES) return WPAD_ERR_BAD_CHANNEL;

	_CPU_ISR_Disable(level);
	if(__wpads_inited==WPAD_STATE_DISABLED) {
		_CPU_ISR_Restore(level);
		return WPAD_ERR_NOT_READY;
	}

	if(__wpads[chan] && WIIMOTE_IS_SET(__wpads[chan],WIIMOTE_STATE_CONNECTED)) {
		if(WIIMOTE_IS_SET(__wpads[chan],WIIMOTE_STATE_HANDSHAKE_COMPLETE)) {
			wpdcb = &__wpdcb[chan];
#ifdef HAVE_WIIUSE_QUEUE_EXT
			if(wpdcb->queue_ext!=NULL) {
				maxbufs = wpdcb->queue_length;
				wpadd = wpdcb->queue_ext;
			}
         else
#endif
         {
				maxbufs = EVENTQUEUE_LENGTH;
				wpadd = wpdcb->queue_int;
			}
			if(wpdcb->queue_full == 0) {
				_CPU_ISR_Restore(level);
				return WPAD_ERR_QUEUE_EMPTY;
			}
			if(data)
				*data = wpadd[wpdcb->queue_head];
			wpdcb->queue_head++;
			wpdcb->queue_head %= maxbufs;
			wpdcb->queue_full--;
			lstate = &wpdcb->lstate;
			accel_calib = &__wpads[chan]->accel_calib;
			smoothed = WIIMOTE_IS_FLAG_SET(__wpads[chan], WIIUSE_SMOOTHING);
		} else {
			_CPU_ISR_Restore(level);
			return WPAD_ERR_NOT_READY;
		}
	} else {
		_CPU_ISR_Restore(level);
		return WPAD_ERR_NO_CONTROLLER;
	}

	_CPU_ISR_Restore(level);
	if(data)
		__wpad_calc_data(data,lstate,accel_calib,smoothed);
	return 0;
}