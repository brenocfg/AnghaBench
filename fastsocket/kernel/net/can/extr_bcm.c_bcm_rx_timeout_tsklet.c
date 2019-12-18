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
struct bcm_op {int /*<<< orphan*/  can_id; int /*<<< orphan*/  ival2; int /*<<< orphan*/  ival1; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; } ;
struct bcm_msg_head {scalar_t__ nframes; int /*<<< orphan*/  can_id; int /*<<< orphan*/  ival2; int /*<<< orphan*/  ival1; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_TIMEOUT ; 
 int /*<<< orphan*/  bcm_send_to_user (struct bcm_op*,struct bcm_msg_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_rx_timeout_tsklet(unsigned long data)
{
	struct bcm_op *op = (struct bcm_op *)data;
	struct bcm_msg_head msg_head;

	/* create notification to user */
	msg_head.opcode  = RX_TIMEOUT;
	msg_head.flags   = op->flags;
	msg_head.count   = op->count;
	msg_head.ival1   = op->ival1;
	msg_head.ival2   = op->ival2;
	msg_head.can_id  = op->can_id;
	msg_head.nframes = 0;

	bcm_send_to_user(op, &msg_head, NULL, 0);
}