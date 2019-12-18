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
struct can_frame {int can_dlc; } ;
struct bcm_op {int frames_filtered; int frames_abs; int /*<<< orphan*/  can_id; int /*<<< orphan*/  ival2; int /*<<< orphan*/  ival1; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; } ;
struct bcm_msg_head {int nframes; int /*<<< orphan*/  can_id; int /*<<< orphan*/  ival2; int /*<<< orphan*/  ival1; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int BCM_CAN_DLC_MASK ; 
 int /*<<< orphan*/  RX_CHANGED ; 
 int RX_RECV ; 
 int ULONG_MAX ; 
 int /*<<< orphan*/  bcm_send_to_user (struct bcm_op*,struct bcm_msg_head*,struct can_frame*,int) ; 

__attribute__((used)) static void bcm_rx_changed(struct bcm_op *op, struct can_frame *data)
{
	struct bcm_msg_head head;

	/* update statistics */
	op->frames_filtered++;

	/* prevent statistics overflow */
	if (op->frames_filtered > ULONG_MAX/100)
		op->frames_filtered = op->frames_abs = 0;

	/* this element is not throttled anymore */
	data->can_dlc &= (BCM_CAN_DLC_MASK|RX_RECV);

	head.opcode  = RX_CHANGED;
	head.flags   = op->flags;
	head.count   = op->count;
	head.ival1   = op->ival1;
	head.ival2   = op->ival2;
	head.can_id  = op->can_id;
	head.nframes = 1;

	bcm_send_to_user(op, &head, data, 1);
}