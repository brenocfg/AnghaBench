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
struct pvr2_hdw {scalar_t__ input_val; int freqSelector; int freqDirty; unsigned long freqValRadio; unsigned long freqValTelevision; scalar_t__ freqSlotTelevision; scalar_t__ freqSlotRadio; } ;

/* Variables and functions */
 scalar_t__ PVR2_CVAL_INPUT_RADIO ; 

__attribute__((used)) static void pvr2_hdw_set_cur_freq(struct pvr2_hdw *hdw,unsigned long val)
{
	if (hdw->input_val == PVR2_CVAL_INPUT_RADIO) {
		if (hdw->freqSelector) {
			/* Swing over to radio frequency selection */
			hdw->freqSelector = 0;
			hdw->freqDirty = !0;
		}
		if (hdw->freqValRadio != val) {
			hdw->freqValRadio = val;
			hdw->freqSlotRadio = 0;
			hdw->freqDirty = !0;
		}
	} else {
		if (!(hdw->freqSelector)) {
			/* Swing over to television frequency selection */
			hdw->freqSelector = 1;
			hdw->freqDirty = !0;
		}
		if (hdw->freqValTelevision != val) {
			hdw->freqValTelevision = val;
			hdw->freqSlotTelevision = 0;
			hdw->freqDirty = !0;
		}
	}
}