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
 int /*<<< orphan*/  NumberLeafs_r (int /*<<< orphan*/ ) ; 
 scalar_t__ num_solidfaces ; 
 scalar_t__ num_visclusters ; 
 scalar_t__ num_visportals ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 

void NumberClusters(tree_t *tree) {
	num_visclusters = 0;
	num_visportals = 0;
	num_solidfaces = 0;

	qprintf ("--- NumberClusters ---\n");
	
	// set the cluster field in every leaf and count the total number of portals
	NumberLeafs_r (tree->headnode);

	qprintf ("%5i visclusters\n", num_visclusters);
	qprintf ("%5i visportals\n", num_visportals);
	qprintf ("%5i solidfaces\n", num_solidfaces);
}