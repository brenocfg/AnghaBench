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
struct TYPE_3__ {int numSurfaces; int firstSurface; } ;
typedef  TYPE_1__ lleaf_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAP_LEAFFACES ; 
 int* clustersurfaces ; 
 TYPE_1__* leafs ; 
 int numclustersurfaces ; 
 int portalclusters ; 

void VL_LinkSurfaceIntoCluster(int cluster, int surfaceNum)
{
	lleaf_t *leaf;
	int i;

	leaf = &leafs[cluster];

	for (i = 0; i < leaf->numSurfaces; i++)
	{
		if (clustersurfaces[leaf->firstSurface + i] == surfaceNum)
			return;
	}
	for (i = numclustersurfaces; i > leaf->firstSurface + leaf->numSurfaces; i--)
		clustersurfaces[i] = clustersurfaces[i-1];
	for (i = 0; i < portalclusters; i++)
	{
		if (i == cluster)
			continue;
		if (leafs[i].firstSurface >= leaf->firstSurface + leaf->numSurfaces)
			leafs[i].firstSurface++;
	}
	clustersurfaces[leaf->firstSurface + leaf->numSurfaces] = surfaceNum;
	leaf->numSurfaces++;
	numclustersurfaces++;
	if (numclustersurfaces >= MAX_MAP_LEAFFACES)
		Error("MAX_MAP_LEAFFACES");
}