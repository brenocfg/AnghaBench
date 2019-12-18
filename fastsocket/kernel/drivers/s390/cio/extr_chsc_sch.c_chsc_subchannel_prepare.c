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
struct subchannel {int /*<<< orphan*/  schid; } ;
struct schib {int /*<<< orphan*/  scsw; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ scsw_stctl (int /*<<< orphan*/ *) ; 
 int stsch_err (int /*<<< orphan*/ ,struct schib*) ; 

__attribute__((used)) static int chsc_subchannel_prepare(struct subchannel *sch)
{
	int cc;
	struct schib schib;
	/*
	 * Don't allow suspend while the subchannel is not idle
	 * since we don't have a way to clear the subchannel and
	 * cannot disable it with a request running.
	 */
	cc = stsch_err(sch->schid, &schib);
	if (!cc && scsw_stctl(&schib.scsw))
		return -EAGAIN;
	return 0;
}