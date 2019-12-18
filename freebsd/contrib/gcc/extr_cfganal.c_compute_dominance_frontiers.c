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
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  TV_DOM_FRONTIERS ; 
 int /*<<< orphan*/  compute_dominance_frontiers_1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

void
compute_dominance_frontiers (bitmap *frontiers)
{
  timevar_push (TV_DOM_FRONTIERS);

  compute_dominance_frontiers_1 (frontiers);

  timevar_pop (TV_DOM_FRONTIERS);
}