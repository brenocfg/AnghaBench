#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* portalfront; int* portalflood; int leaf; scalar_t__ removed; } ;
typedef  TYPE_1__ vportal_t ;
struct TYPE_7__ {int numportals; TYPE_1__** portals; } ;
typedef  TYPE_2__ leaf_t ;

/* Variables and functions */
 TYPE_2__* leafs ; 
 TYPE_1__* portals ; 

void SimpleFlood (vportal_t *srcportal, int leafnum)
{
	int		i;
	leaf_t	*leaf;
	vportal_t	*p;
	int		pnum;

	leaf = &leafs[leafnum];
	
	for (i=0 ; i<leaf->numportals ; i++)
	{
		p = leaf->portals[i];
		if (p->removed)
			continue;
		pnum = p - portals;
		if ( ! (srcportal->portalfront[pnum>>3] & (1<<(pnum&7)) ) )
			continue;

		if (srcportal->portalflood[pnum>>3] & (1<<(pnum&7)) )
			continue;

		srcportal->portalflood[pnum>>3] |= (1<<(pnum&7));
		
		SimpleFlood (srcportal, p->leaf);
	}
}