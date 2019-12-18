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

/* Variables and functions */
 int /*<<< orphan*/  BasePortalVis ; 
 int /*<<< orphan*/  CalcFastVis () ; 
 int /*<<< orphan*/  CalcPassagePortalVis () ; 
 int /*<<< orphan*/  CalcPassageVis () ; 
 int /*<<< orphan*/  CalcPortalVis () ; 
 int /*<<< orphan*/  ClusterMerge (int) ; 
 int /*<<< orphan*/  RunThreadsOnIndividual (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SortPortals () ; 
 int /*<<< orphan*/  _printf (char*,...) ; 
 scalar_t__ fastvis ; 
 scalar_t__ noPassageVis ; 
 int numportals ; 
 scalar_t__ passageVisOnly ; 
 int portalclusters ; 
 int /*<<< orphan*/  qtrue ; 
 int totalvis ; 

void CalcVis (void)
{
	int		i;

	RunThreadsOnIndividual (numportals*2, qtrue, BasePortalVis);

//	RunThreadsOnIndividual (numportals*2, qtrue, BetterPortalVis);

	SortPortals ();

	if (fastvis) {
		CalcFastVis();
	}
	else if ( noPassageVis ) {
		CalcPortalVis();
	}
	else if ( passageVisOnly ) {
		CalcPassageVis();
	}
	else {
		CalcPassagePortalVis();
	}
	//
	// assemble the leaf vis lists by oring and compressing the portal lists
	//
	_printf("creating leaf vis...\n");
	for (i=0 ; i<portalclusters ; i++)
		ClusterMerge (i);

	_printf( "Total visible clusters: %i\n", totalvis );
	_printf( "Average clusters visible: %i\n", totalvis / portalclusters );
}