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
typedef  scalar_t__ u8 ;
struct dst_state {int type_flags; scalar_t__* rxbuffer; int /*<<< orphan*/  dst_mutex; } ;

/* Variables and functions */
 scalar_t__ ACK ; 
 int /*<<< orphan*/  DST_DEBUG ; 
 int /*<<< orphan*/  DST_ERROR ; 
 int /*<<< orphan*/  DST_INFO ; 
 int /*<<< orphan*/  DST_NOTICE ; 
 int DST_TYPE_HAS_FW_1 ; 
 int EIO ; 
 int /*<<< orphan*/  FIXED_COMM ; 
 int /*<<< orphan*/  GET_ACK ; 
 int /*<<< orphan*/  NO_DELAY ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 scalar_t__ dst_check_sum (scalar_t__*,int) ; 
 scalar_t__ dst_comm_init (struct dst_state*) ; 
 scalar_t__ dst_error_recovery (struct dst_state*) ; 
 scalar_t__ dst_pio_disable (struct dst_state*) ; 
 int /*<<< orphan*/  dst_wait_dst_ready (struct dst_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ read_dst (struct dst_state*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  verbose ; 
 scalar_t__ write_dst (struct dst_state*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int dst_command(struct dst_state *state, u8 *data, u8 len)
{
	u8 reply;

	mutex_lock(&state->dst_mutex);
	if ((dst_comm_init(state)) < 0) {
		dprintk(verbose, DST_NOTICE, 1, "DST Communication Initialization Failed.");
		goto error;
	}
	if (write_dst(state, data, len)) {
		dprintk(verbose, DST_INFO, 1, "Trying to recover.. ");
		if ((dst_error_recovery(state)) < 0) {
			dprintk(verbose, DST_ERROR, 1, "Recovery Failed.");
			goto error;
		}
		goto error;
	}
	if ((dst_pio_disable(state)) < 0) {
		dprintk(verbose, DST_ERROR, 1, "PIO Disable Failed.");
		goto error;
	}
	if (state->type_flags & DST_TYPE_HAS_FW_1)
		mdelay(3);
	if (read_dst(state, &reply, GET_ACK)) {
		dprintk(verbose, DST_DEBUG, 1, "Trying to recover.. ");
		if ((dst_error_recovery(state)) < 0) {
			dprintk(verbose, DST_INFO, 1, "Recovery Failed.");
			goto error;
		}
		goto error;
	}
	if (reply != ACK) {
		dprintk(verbose, DST_INFO, 1, "write not acknowledged 0x%02x ", reply);
		goto error;
	}
	if (len >= 2 && data[0] == 0 && (data[1] == 1 || data[1] == 3))
		goto error;
	if (state->type_flags & DST_TYPE_HAS_FW_1)
		mdelay(3);
	else
		udelay(2000);
	if (!dst_wait_dst_ready(state, NO_DELAY))
		goto error;
	if (read_dst(state, state->rxbuffer, FIXED_COMM)) {
		dprintk(verbose, DST_DEBUG, 1, "Trying to recover.. ");
		if ((dst_error_recovery(state)) < 0) {
			dprintk(verbose, DST_INFO, 1, "Recovery failed.");
			goto error;
		}
		goto error;
	}
	if (state->rxbuffer[7] != dst_check_sum(state->rxbuffer, 7)) {
		dprintk(verbose, DST_INFO, 1, "checksum failure");
		goto error;
	}
	mutex_unlock(&state->dst_mutex);
	return 0;

error:
	mutex_unlock(&state->dst_mutex);
	return -EIO;

}