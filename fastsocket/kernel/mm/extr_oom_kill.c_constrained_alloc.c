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
struct zonelist {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum oom_constraint { ____Placeholder_oom_constraint } oom_constraint ;

/* Variables and functions */
 int CONSTRAINT_NONE ; 
 unsigned long total_swap_pages ; 
 unsigned long totalram_pages ; 

__attribute__((used)) static enum oom_constraint constrained_alloc(struct zonelist *zonelist,
				gfp_t gfp_mask, nodemask_t *nodemask,
				unsigned long *totalpages)
{
	*totalpages = totalram_pages + total_swap_pages;
	return CONSTRAINT_NONE;
}