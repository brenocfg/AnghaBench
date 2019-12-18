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
struct w6692_hw {int /*<<< orphan*/  name; } ;
struct mISDN_ctrl_req {int op; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MISDN_CTRL_GETOP 128 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
channel_ctrl(struct w6692_hw *card, struct mISDN_ctrl_req *cq)
{
	int	ret = 0;

	switch (cq->op) {
	case MISDN_CTRL_GETOP:
		cq->op = 0;
		break;
	default:
		pr_info("%s: unknown CTRL OP %x\n", card->name, cq->op);
		ret = -EINVAL;
		break;
	}
	return ret;
}