#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
struct sym_tcb {TYPE_1__* starget; } ;
struct TYPE_4__ {scalar_t__ reqtags; scalar_t__ scdev_depth; } ;
struct sym_lcb {TYPE_2__ s; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,scalar_t__) ; 
 struct sym_lcb* sym_lp (struct sym_tcb*,int) ; 

__attribute__((used)) static void sym_tune_dev_queuing(struct sym_tcb *tp, int lun, u_short reqtags)
{
	struct sym_lcb *lp = sym_lp(tp, lun);
	u_short	oldtags;

	if (!lp)
		return;

	oldtags = lp->s.reqtags;

	if (reqtags > lp->s.scdev_depth)
		reqtags = lp->s.scdev_depth;

	lp->s.reqtags     = reqtags;

	if (reqtags != oldtags) {
		dev_info(&tp->starget->dev,
		         "tagged command queuing %s, command queue depth %d.\n",
		          lp->s.reqtags ? "enabled" : "disabled", reqtags);
	}
}