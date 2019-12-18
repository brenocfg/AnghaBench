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
struct dst_state {int* messages; } ;
typedef  int /*<<< orphan*/  slot_command ;

/* Variables and functions */
 int /*<<< orphan*/  CA_INFO ; 
 int /*<<< orphan*/  DST_CA_ERROR ; 
 int /*<<< orphan*/  DST_CA_INFO ; 
 int /*<<< orphan*/  GET_REPLY ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 scalar_t__ dst_put_ci (struct dst_state*,int*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_checksum (int*,int) ; 
 int /*<<< orphan*/  put_command_and_length (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int ca_get_ca_info(struct dst_state *state)
{
	int srcPtr, dstPtr, i, num_ids;
	static u8 slot_command[8] = {0x07, 0x40, 0x00, 0x00, 0x02, 0x00, 0x00, 0xff};
	const int in_system_id_pos = 8, out_system_id_pos = 4, in_num_ids_pos = 7;

	put_checksum(&slot_command[0], slot_command[0]);
	if ((dst_put_ci(state, slot_command, sizeof (slot_command), state->messages, GET_REPLY)) < 0) {
		dprintk(verbose, DST_CA_ERROR, 1, " -->dst_put_ci FAILED !");
		return -1;
	}
	dprintk(verbose, DST_CA_INFO, 1, " -->dst_put_ci SUCCESS !");

	// Print raw data
	dprintk(verbose, DST_CA_INFO, 0, " DST data = [");
	for (i = 0; i < state->messages[0] + 1; i++) {
		dprintk(verbose, DST_CA_INFO, 0, " 0x%02x", state->messages[i]);
	}
	dprintk(verbose, DST_CA_INFO, 0, "]\n");

	// Set the command and length of the output
	num_ids = state->messages[in_num_ids_pos];
	if (num_ids >= 100) {
		num_ids = 100;
		dprintk(verbose, DST_CA_ERROR, 1, "Invalid number of ids (>100). Recovering.");
	}
	put_command_and_length(&state->messages[0], CA_INFO, num_ids * 2);

	dprintk(verbose, DST_CA_INFO, 0, " CA_INFO = [");
	srcPtr = in_system_id_pos;
	dstPtr = out_system_id_pos;
	for(i = 0; i < num_ids; i++) {
		dprintk(verbose, DST_CA_INFO, 0, " 0x%02x%02x", state->messages[srcPtr + 0], state->messages[srcPtr + 1]);
		// Append to output
		state->messages[dstPtr + 0] = state->messages[srcPtr + 0];
		state->messages[dstPtr + 1] = state->messages[srcPtr + 1];
		srcPtr += 2;
		dstPtr += 2;
	}
	dprintk(verbose, DST_CA_INFO, 0, "]\n");

	return 0;
}