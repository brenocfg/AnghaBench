#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  opcode__sgloffset; } ;
struct TYPE_13__ {int /*<<< orphan*/  error; } ;
struct TYPE_17__ {TYPE_1__ status_block; } ;
struct TYPE_14__ {TYPE_6__ oldcommand; } ;
struct TYPE_16__ {TYPE_2__ command; } ;
struct TYPE_15__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * state; TYPE_4__** command_packet_virt; int /*<<< orphan*/  posted_request_count; scalar_t__* generic_buffer_virt; } ;
typedef  TYPE_3__ TW_Device_Extension ;
typedef  TYPE_4__ TW_Command_Full ;
typedef  TYPE_5__ TW_Command_Apache_Header ;
typedef  TYPE_6__ TW_Command ;

/* Variables and functions */
#define  TW_AEN_QUEUE_EMPTY 129 
#define  TW_AEN_SYNC_TIME_WITH_HOST 128 
 int /*<<< orphan*/  TW_IN_ATTENTION_LOOP ; 
 scalar_t__ TW_OP_OUT (int /*<<< orphan*/ ) ; 
 scalar_t__ TW_OP_SET_PARAM ; 
 int /*<<< orphan*/  TW_S_COMPLETED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl_aen_queue_event (TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ twl_aen_read_queue (TYPE_3__*,int) ; 
 int /*<<< orphan*/  twl_aen_sync_time (TYPE_3__*,int) ; 
 int /*<<< orphan*/  twl_free_request_id (TYPE_3__*,int) ; 

__attribute__((used)) static int twl_aen_complete(TW_Device_Extension *tw_dev, int request_id)
{
	TW_Command_Full *full_command_packet;
	TW_Command *command_packet;
	TW_Command_Apache_Header *header;
	unsigned short aen;
	int retval = 1;

	header = (TW_Command_Apache_Header *)tw_dev->generic_buffer_virt[request_id];
	tw_dev->posted_request_count--;
	aen = le16_to_cpu(header->status_block.error);
	full_command_packet = tw_dev->command_packet_virt[request_id];
	command_packet = &full_command_packet->command.oldcommand;

	/* First check for internal completion of set param for time sync */
	if (TW_OP_OUT(command_packet->opcode__sgloffset) == TW_OP_SET_PARAM) {
		/* Keep reading the queue in case there are more aen's */
		if (twl_aen_read_queue(tw_dev, request_id))
			goto out2;
	        else {
			retval = 0;
			goto out;
		}
	}

	switch (aen) {
	case TW_AEN_QUEUE_EMPTY:
		/* Quit reading the queue if this is the last one */
		break;
	case TW_AEN_SYNC_TIME_WITH_HOST:
		twl_aen_sync_time(tw_dev, request_id);
		retval = 0;
		goto out;
	default:
		twl_aen_queue_event(tw_dev, header);

		/* If there are more aen's, keep reading the queue */
		if (twl_aen_read_queue(tw_dev, request_id))
			goto out2;
		else {
			retval = 0;
			goto out;
		}
	}
	retval = 0;
out2:
	tw_dev->state[request_id] = TW_S_COMPLETED;
	twl_free_request_id(tw_dev, request_id);
	clear_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags);
out:
	return retval;
}