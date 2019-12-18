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
struct raw3270_request {int /*<<< orphan*/  rescnt; int /*<<< orphan*/  rc; } ;
struct TYPE_3__ {int dstat; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {TYPE_2__ scsw; } ;
struct con3270 {int dummy; } ;

/* Variables and functions */
 int DEV_STAT_ATTENTION ; 
 int DEV_STAT_UNIT_CHECK ; 
 int /*<<< orphan*/  EIO ; 
 int RAW3270_IO_DONE ; 
 int /*<<< orphan*/  con3270_issue_read (struct con3270*) ; 

__attribute__((used)) static int
con3270_irq(struct con3270 *cp, struct raw3270_request *rq, struct irb *irb)
{
	/* Handle ATTN. Schedule tasklet to read aid. */
	if (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION)
		con3270_issue_read(cp);

	if (rq) {
		if (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)
			rq->rc = -EIO;
		else
			/* Normal end. Copy residual count. */
			rq->rescnt = irb->scsw.cmd.count;
	}
	return RAW3270_IO_DONE;
}