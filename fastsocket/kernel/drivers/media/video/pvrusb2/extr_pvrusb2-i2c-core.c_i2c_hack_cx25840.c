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
typedef  int u16 ;
struct pvr2_hdw {int i2c_cx25840_hack_state; int /*<<< orphan*/ ** i2c_func; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PVR2_TRACE_CHIPS ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  pvr2_hdw_render_useless (struct pvr2_hdw*) ; 
 int pvr2_i2c_basic_op (struct pvr2_hdw*,int,int*,int,int*,int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int i2c_hack_cx25840(struct pvr2_hdw *hdw,
			    u8 i2c_addr,u8 *wdata,u16 wlen,u8 *rdata,u16 rlen)
{
	int ret;
	unsigned int subaddr;
	u8 wbuf[2];
	int state = hdw->i2c_cx25840_hack_state;

	if (!(rlen || wlen)) {
		// Probe attempt - always just succeed and don't bother the
		// hardware (this helps to make the state machine further
		// down somewhat easier).
		return 0;
	}

	if (state == 3) {
		return pvr2_i2c_basic_op(hdw,i2c_addr,wdata,wlen,rdata,rlen);
	}

	/* We're looking for the exact pattern where the revision register
	   is being read.  The cx25840 module will always look at the
	   revision register first.  Any other pattern of access therefore
	   has to be a probe attempt from somebody else so we'll reject it.
	   Normally we could just let each client just probe the part
	   anyway, but when the cx25840 is wedged, msp3400 will get a false
	   positive and that just screws things up... */

	if (wlen == 0) {
		switch (state) {
		case 1: subaddr = 0x0100; break;
		case 2: subaddr = 0x0101; break;
		default: goto fail;
		}
	} else if (wlen == 2) {
		subaddr = (wdata[0] << 8) | wdata[1];
		switch (subaddr) {
		case 0x0100: state = 1; break;
		case 0x0101: state = 2; break;
		default: goto fail;
		}
	} else {
		goto fail;
	}
	if (!rlen) goto success;
	state = 0;
	if (rlen != 1) goto fail;

	/* If we get to here then we have a legitimate read for one of the
	   two revision bytes, so pass it through. */
	wbuf[0] = subaddr >> 8;
	wbuf[1] = subaddr;
	ret = pvr2_i2c_basic_op(hdw,i2c_addr,wbuf,2,rdata,rlen);

	if ((ret != 0) || (*rdata == 0x04) || (*rdata == 0x0a)) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "WARNING: Detected a wedged cx25840 chip;"
			   " the device will not work.");
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "WARNING: Try power cycling the pvrusb2 device.");
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "WARNING: Disabling further access to the device"
			   " to prevent other foul-ups.");
		// This blocks all further communication with the part.
		hdw->i2c_func[0x44] = NULL;
		pvr2_hdw_render_useless(hdw);
		goto fail;
	}

	/* Success! */
	pvr2_trace(PVR2_TRACE_CHIPS,"cx25840 appears to be OK.");
	state = 3;

 success:
	hdw->i2c_cx25840_hack_state = state;
	return 0;

 fail:
	hdw->i2c_cx25840_hack_state = state;
	return -EIO;
}