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
struct pvr2_hdw {int /*<<< orphan*/  ctl_lock; int /*<<< orphan*/ * cmd_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FX2CMD_GET_EEPROM_ADDR ; 
 int HZ ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVR2_TRACE_INIT ; 
 int pvr2_send_request_ex (struct pvr2_hdw*,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int pvr2_hdw_check_firmware(struct pvr2_hdw *hdw)
{
	/* Try a harmless request to fetch the eeprom's address over
	   endpoint 1.  See what happens.  Only the full FX2 image can
	   respond to this.  If this probe fails then likely the FX2
	   firmware needs be loaded. */
	int result;
	LOCK_TAKE(hdw->ctl_lock); do {
		hdw->cmd_buffer[0] = FX2CMD_GET_EEPROM_ADDR;
		result = pvr2_send_request_ex(hdw,HZ*1,!0,
					   hdw->cmd_buffer,1,
					   hdw->cmd_buffer,1);
		if (result < 0) break;
	} while(0); LOCK_GIVE(hdw->ctl_lock);
	if (result) {
		pvr2_trace(PVR2_TRACE_INIT,
			   "Probe of device endpoint 1 result status %d",
			   result);
	} else {
		pvr2_trace(PVR2_TRACE_INIT,
			   "Probe of device endpoint 1 succeeded");
	}
	return result == 0;
}