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
struct TYPE_2__ {scalar_t__ ena; } ;
struct subchannel {int /*<<< orphan*/  schid; TYPE_1__ config; int /*<<< orphan*/  dev; } ;
struct irb {int dummy; } ;
typedef  int /*<<< orphan*/  ret ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_HEX_EVENT (int,int*,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int EBUSY ; 
 int ENODEV ; 
 int cio_commit_config (struct subchannel*) ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ sch_is_pseudo_sch (struct subchannel*) ; 
 scalar_t__ tsch (int /*<<< orphan*/ ,struct irb*) ; 

int cio_disable_subchannel(struct subchannel *sch)
{
	int retry;
	int ret;

	CIO_TRACE_EVENT(2, "dissch");
	CIO_TRACE_EVENT(2, dev_name(&sch->dev));

	if (sch_is_pseudo_sch(sch))
		return 0;
	if (cio_update_schib(sch))
		return -ENODEV;

	sch->config.ena = 0;

	for (retry = 0; retry < 3; retry++) {
		ret = cio_commit_config(sch);
		if (ret == -EBUSY) {
			struct irb irb;
			if (tsch(sch->schid, &irb) != 0)
				break;
		} else
			break;
	}
	CIO_HEX_EVENT(2, &ret, sizeof(ret));
	return ret;
}