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
typedef  int /*<<< orphan*/  u64 ;
struct cgroup {int dummy; } ;
struct cftype {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  prioidx; } ;

/* Variables and functions */
 TYPE_1__* cgrp_netprio_state (struct cgroup*) ; 

__attribute__((used)) static u64 read_prioidx(struct cgroup *cgrp, struct cftype *cft)
{
	return (u64)cgrp_netprio_state(cgrp)->prioidx;
}