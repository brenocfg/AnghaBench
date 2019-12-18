#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  actl; } ;
struct TYPE_5__ {TYPE_1__ eadm; } ;
struct TYPE_6__ {TYPE_2__ scsw; } ;
struct subchannel {TYPE_3__ schib; int /*<<< orphan*/  schid; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SCSW_ACTL_CLEAR_PEND ; 
 int csch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eadm_subchannel_clear(struct subchannel *sch)
{
	int cc;

	cc = csch(sch->schid);
	if (cc)
		return -ENODEV;

	sch->schib.scsw.eadm.actl |= SCSW_ACTL_CLEAR_PEND;
	return 0;
}