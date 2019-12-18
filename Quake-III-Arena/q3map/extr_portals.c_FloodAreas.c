#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  CheckAreas_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindAreas_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_areas ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 

void FloodAreas (tree_t *tree)
{
	qprintf ("--- FloodAreas ---\n");
	FindAreas_r( tree->headnode );

	// check for areaportal brushes that don't touch two areas
	CheckAreas_r( tree->headnode );

	qprintf ("%5i areas\n", c_areas);
}