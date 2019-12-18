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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct pvr2_hdw {int* cmd_buffer; int /*<<< orphan*/  ctl_lock; } ;

/* Variables and functions */
 int EIO ; 
 int FX2CMD_GET_IR_CODE ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 unsigned int pvr2_send_request (struct pvr2_hdw*,int*,int,int*,int) ; 

__attribute__((used)) static int i2c_24xxx_ir(struct pvr2_hdw *hdw,
			u8 i2c_addr,u8 *wdata,u16 wlen,u8 *rdata,u16 rlen)
{
	u8 dat[4];
	unsigned int stat;

	if (!(rlen || wlen)) {
		/* This is a probe attempt.  Just let it succeed. */
		return 0;
	}

	/* We don't understand this kind of transaction */
	if ((wlen != 0) || (rlen == 0)) return -EIO;

	if (rlen < 3) {
		/* Mike Isely <isely@pobox.com> Appears to be a probe
		   attempt from lirc.  Just fill in zeroes and return.  If
		   we try instead to do the full transaction here, then bad
		   things seem to happen within the lirc driver module
		   (version 0.8.0-7 sources from Debian, when run under
		   vanilla 2.6.17.6 kernel) - and I don't have the patience
		   to chase it down. */
		if (rlen > 0) rdata[0] = 0;
		if (rlen > 1) rdata[1] = 0;
		return 0;
	}

	/* Issue a command to the FX2 to read the IR receiver. */
	LOCK_TAKE(hdw->ctl_lock); do {
		hdw->cmd_buffer[0] = FX2CMD_GET_IR_CODE;
		stat = pvr2_send_request(hdw,
					 hdw->cmd_buffer,1,
					 hdw->cmd_buffer,4);
		dat[0] = hdw->cmd_buffer[0];
		dat[1] = hdw->cmd_buffer[1];
		dat[2] = hdw->cmd_buffer[2];
		dat[3] = hdw->cmd_buffer[3];
	} while (0); LOCK_GIVE(hdw->ctl_lock);

	/* Give up if that operation failed. */
	if (stat != 0) return stat;

	/* Mangle the results into something that looks like the real IR
	   receiver. */
	rdata[2] = 0xc1;
	if (dat[0] != 1) {
		/* No code received. */
		rdata[0] = 0;
		rdata[1] = 0;
	} else {
		u16 val;
		/* Mash the FX2 firmware-provided IR code into something
		   that the normal i2c chip-level driver expects. */
		val = dat[1];
		val <<= 8;
		val |= dat[2];
		val >>= 1;
		val &= ~0x0003;
		val |= 0x8000;
		rdata[0] = (val >> 8) & 0xffu;
		rdata[1] = val & 0xffu;
	}

	return 0;
}