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
typedef  scalar_t__ u16 ;
struct pvr2_hdw {int fw_size; int fw_cpu_flag; scalar_t__ fw_buffer; int /*<<< orphan*/  big_lock; int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 scalar_t__ EEPROM_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVR2_TRACE_FIRMWARE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pvr2_full_eeprom_fetch (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_hdw_cpureset_assert (struct pvr2_hdw*,int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 int usb_control_msg (int /*<<< orphan*/ ,unsigned int,int,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 unsigned int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pvr2_hdw_cpufw_set_enabled(struct pvr2_hdw *hdw,
				int mode,
				int enable_flag)
{
	int ret;
	u16 address;
	unsigned int pipe;
	LOCK_TAKE(hdw->big_lock); do {
		if ((hdw->fw_buffer == NULL) == !enable_flag) break;

		if (!enable_flag) {
			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Cleaning up after CPU firmware fetch");
			kfree(hdw->fw_buffer);
			hdw->fw_buffer = NULL;
			hdw->fw_size = 0;
			if (hdw->fw_cpu_flag) {
				/* Now release the CPU.  It will disconnect
				   and reconnect later. */
				pvr2_hdw_cpureset_assert(hdw,0);
			}
			break;
		}

		hdw->fw_cpu_flag = (mode != 2);
		if (hdw->fw_cpu_flag) {
			hdw->fw_size = (mode == 1) ? 0x4000 : 0x2000;
			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Preparing to suck out CPU firmware"
				   " (size=%u)", hdw->fw_size);
			hdw->fw_buffer = kzalloc(hdw->fw_size,GFP_KERNEL);
			if (!hdw->fw_buffer) {
				hdw->fw_size = 0;
				break;
			}

			/* We have to hold the CPU during firmware upload. */
			pvr2_hdw_cpureset_assert(hdw,1);

			/* download the firmware from address 0000-1fff in 2048
			   (=0x800) bytes chunk. */

			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Grabbing CPU firmware");
			pipe = usb_rcvctrlpipe(hdw->usb_dev, 0);
			for(address = 0; address < hdw->fw_size;
			    address += 0x800) {
				ret = usb_control_msg(hdw->usb_dev,pipe,
						      0xa0,0xc0,
						      address,0,
						      hdw->fw_buffer+address,
						      0x800,HZ);
				if (ret < 0) break;
			}

			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Done grabbing CPU firmware");
		} else {
			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Sucking down EEPROM contents");
			hdw->fw_buffer = pvr2_full_eeprom_fetch(hdw);
			if (!hdw->fw_buffer) {
				pvr2_trace(PVR2_TRACE_FIRMWARE,
					   "EEPROM content suck failed.");
				break;
			}
			hdw->fw_size = EEPROM_SIZE;
			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Done sucking down EEPROM contents");
		}

	} while (0); LOCK_GIVE(hdw->big_lock);
}