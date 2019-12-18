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
struct cgroup {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_REMOVED ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

inline int cgroup_is_removed(const struct cgroup *cgrp)
{
	return test_bit(CGRP_REMOVED, &cgrp->flags);
}