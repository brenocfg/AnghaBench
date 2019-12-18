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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int ena; scalar_t__ csense; int /*<<< orphan*/  intparm; int /*<<< orphan*/  isc; } ;
struct subchannel {int /*<<< orphan*/  schid; TYPE_1__ config; int /*<<< orphan*/  isc; int /*<<< orphan*/  dev; } ;
struct irb {int dummy; } ;
typedef  int /*<<< orphan*/  ret ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_HEX_EVENT (int,int*,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int cio_commit_config (struct subchannel*) ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ sch_is_pseudo_sch (struct subchannel*) ; 
 scalar_t__ tsch (int /*<<< orphan*/ ,struct irb*) ; 

int cio_enable_subchannel(struct subchannel *sch, u32 intparm)
{
	int retry;
	int ret;

	CIO_TRACE_EVENT(2, "ensch");
	CIO_TRACE_EVENT(2, dev_name(&sch->dev));

	if (sch_is_pseudo_sch(sch))
		return -EINVAL;
	if (cio_update_schib(sch))
		return -ENODEV;

	sch->config.ena = 1;
	sch->config.isc = sch->isc;
	sch->config.intparm = intparm;

	for (retry = 0; retry < 3; retry++) {
		ret = cio_commit_config(sch);
		if (ret == -EIO) {
			/*
			 * Got a program check in msch. Try without
			 * the concurrent sense bit the next time.
			 */
			sch->config.csense = 0;
		} else if (ret == -EBUSY) {
			struct irb irb;
			if (tsch(sch->schid, &irb) != 0)
				break;
		} else
			break;
	}
	CIO_HEX_EVENT(2, &ret, sizeof(ret));
	return ret;
}