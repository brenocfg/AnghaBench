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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct intel_dp {int dummy; } ;

/* Variables and functions */
 int AUX_NATIVE_REPLY_ACK ; 
 int AUX_NATIVE_REPLY_DEFER ; 
 int AUX_NATIVE_REPLY_MASK ; 
 int AUX_NATIVE_WRITE ; 
 int EIO ; 
 int intel_dp_aux_ch (struct intel_dp*,int*,int,int*,int) ; 
 int /*<<< orphan*/  intel_dp_check_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
intel_dp_aux_native_write(struct intel_dp *intel_dp,
			  uint16_t address, uint8_t *send, int send_bytes)
{
	int ret;
	uint8_t	msg[20];
	int msg_bytes;
	uint8_t	ack;

	intel_dp_check_edp(intel_dp);
	if (send_bytes > 16)
		return -1;
	msg[0] = AUX_NATIVE_WRITE << 4;
	msg[1] = address >> 8;
	msg[2] = address & 0xff;
	msg[3] = send_bytes - 1;
	memcpy(&msg[4], send, send_bytes);
	msg_bytes = send_bytes + 4;
	for (;;) {
		ret = intel_dp_aux_ch(intel_dp, msg, msg_bytes, &ack, 1);
		if (ret < 0)
			return ret;
		if ((ack & AUX_NATIVE_REPLY_MASK) == AUX_NATIVE_REPLY_ACK)
			break;
		else if ((ack & AUX_NATIVE_REPLY_MASK) == AUX_NATIVE_REPLY_DEFER)
			udelay(100);
		else
			return -EIO;
	}
	return send_bytes;
}