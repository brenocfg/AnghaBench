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
struct dst_state {int diseq_flags; int type_flags; scalar_t__ dst_type; int* rx_tuna; int decode_freq; int decode_lock; } ;

/* Variables and functions */
 int ATTEMPT_TUNE ; 
 int /*<<< orphan*/  DST_DEBUG ; 
 int /*<<< orphan*/  DST_INFO ; 
 int DST_TYPE_HAS_VLF ; 
 scalar_t__ DST_TYPE_IS_ATSC ; 
 scalar_t__ DST_TYPE_IS_SAT ; 
 int EIO ; 
 int FIXED_COMM ; 
 int HAS_LOCK ; 
 int /*<<< orphan*/  NO_DELAY ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int dst_check_sum (int*,int) ; 
 int /*<<< orphan*/  dst_wait_dst_ready (struct dst_state*,int /*<<< orphan*/ ) ; 
 int read_dst (struct dst_state*,int*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int dst_get_tuna(struct dst_state *state)
{
	int retval;

	if ((state->diseq_flags & ATTEMPT_TUNE) == 0)
		return 0;
	state->diseq_flags &= ~(HAS_LOCK);
	if (!dst_wait_dst_ready(state, NO_DELAY))
		return -EIO;
	if ((state->type_flags & DST_TYPE_HAS_VLF) &&
		!(state->dst_type == DST_TYPE_IS_ATSC))

		retval = read_dst(state, state->rx_tuna, 10);
	else
		retval = read_dst(state, &state->rx_tuna[2], FIXED_COMM);
	if (retval < 0) {
		dprintk(verbose, DST_DEBUG, 1, "read not successful");
		return retval;
	}
	if ((state->type_flags & DST_TYPE_HAS_VLF) &&
	   !(state->dst_type == DST_TYPE_IS_ATSC)) {

		if (state->rx_tuna[9] != dst_check_sum(&state->rx_tuna[0], 9)) {
			dprintk(verbose, DST_INFO, 1, "checksum failure ? ");
			return -EIO;
		}
	} else {
		if (state->rx_tuna[9] != dst_check_sum(&state->rx_tuna[2], 7)) {
			dprintk(verbose, DST_INFO, 1, "checksum failure? ");
			return -EIO;
		}
	}
	if (state->rx_tuna[2] == 0 && state->rx_tuna[3] == 0)
		return 0;
	if (state->dst_type == DST_TYPE_IS_SAT) {
		state->decode_freq = ((state->rx_tuna[2] & 0x7f) << 8) + state->rx_tuna[3];
	} else {
		state->decode_freq = ((state->rx_tuna[2] & 0x7f) << 16) + (state->rx_tuna[3] << 8) + state->rx_tuna[4];
	}
	state->decode_freq = state->decode_freq * 1000;
	state->decode_lock = 1;
	state->diseq_flags |= HAS_LOCK;

	return 1;
}