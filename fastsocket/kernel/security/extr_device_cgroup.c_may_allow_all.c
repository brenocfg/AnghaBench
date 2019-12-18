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
struct dev_cgroup {scalar_t__ behavior; } ;

/* Variables and functions */
 scalar_t__ DEVCG_DEFAULT_ALLOW ; 

__attribute__((used)) static inline int may_allow_all(struct dev_cgroup *parent)
{
	if (!parent)
		return 1;
	return parent->behavior == DEVCG_DEFAULT_ALLOW;
}