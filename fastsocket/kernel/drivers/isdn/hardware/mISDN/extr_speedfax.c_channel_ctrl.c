#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* ctrl ) (TYPE_1__*,int /*<<< orphan*/ ,int) ;} ;
struct sfax_hw {int /*<<< orphan*/  name; TYPE_1__ isac; } ;
struct mISDN_ctrl_req {int op; int channel; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HW_TESTLOOP ; 
#define  MISDN_CTRL_GETOP 129 
#define  MISDN_CTRL_LOOP 128 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
channel_ctrl(struct sfax_hw  *sf, struct mISDN_ctrl_req *cq)
{
	int	ret = 0;

	switch (cq->op) {
	case MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_LOOP;
		break;
	case MISDN_CTRL_LOOP:
		/* cq->channel: 0 disable, 1 B1 loop 2 B2 loop, 3 both */
		if (cq->channel < 0 || cq->channel > 3) {
			ret = -EINVAL;
			break;
		}
		ret = sf->isac.ctrl(&sf->isac, HW_TESTLOOP, cq->channel);
		break;
	default:
		pr_info("%s: unknown Op %x\n", sf->name, cq->op);
		ret = -EINVAL;
		break;
	}
	return ret;
}