#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  MakeHeadnodePortals (TYPE_1__*) ; 
 int /*<<< orphan*/  MakeTreePortals_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_tinyportals ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 

void MakeTreePortals (tree_t *tree)
{
	qprintf( "----- MakeTreePortals -----\n");
	MakeHeadnodePortals (tree);
	MakeTreePortals_r (tree->headnode);
	qprintf("%6d tiny portals\n", c_tinyportals);
}