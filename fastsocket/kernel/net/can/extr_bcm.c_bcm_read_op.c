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
struct list_head {int dummy; } ;
struct bcm_op {int /*<<< orphan*/  frames; int /*<<< orphan*/  nframes; int /*<<< orphan*/  ival2; int /*<<< orphan*/  ival1; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; } ;
struct bcm_msg_head {int /*<<< orphan*/  nframes; int /*<<< orphan*/  ival2; int /*<<< orphan*/  ival1; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; int /*<<< orphan*/  can_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int MHSIZ ; 
 struct bcm_op* bcm_find_op (struct list_head*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm_send_to_user (struct bcm_op*,struct bcm_msg_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_read_op(struct list_head *ops, struct bcm_msg_head *msg_head,
		       int ifindex)
{
	struct bcm_op *op = bcm_find_op(ops, msg_head->can_id, ifindex);

	if (!op)
		return -EINVAL;

	/* put current values into msg_head */
	msg_head->flags   = op->flags;
	msg_head->count   = op->count;
	msg_head->ival1   = op->ival1;
	msg_head->ival2   = op->ival2;
	msg_head->nframes = op->nframes;

	bcm_send_to_user(op, msg_head, op->frames, 0);

	return MHSIZ;
}