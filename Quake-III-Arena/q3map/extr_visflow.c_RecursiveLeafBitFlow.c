#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int leaf; scalar_t__ portalflood; scalar_t__ removed; } ;
typedef  TYPE_1__ vportal_t ;
struct TYPE_6__ {int numportals; TYPE_1__** portals; } ;
typedef  TYPE_2__ leaf_t ;
typedef  int byte ;

/* Variables and functions */
 int MAX_PORTALS ; 
 TYPE_2__* leafs ; 
 int portallongs ; 
 TYPE_1__* portals ; 

void RecursiveLeafBitFlow (int leafnum, byte *mightsee, byte *cansee)
{
	vportal_t	*p;
	leaf_t 		*leaf;
	int			i, j;
	long		more;
	int			pnum;
	byte		newmight[MAX_PORTALS/8];

	leaf = &leafs[leafnum];
	
	// check all portals for flowing into other leafs
	for (i=0 ; i<leaf->numportals ; i++)
	{
		p = leaf->portals[i];
		if (p->removed)
			continue;
		pnum = p - portals;

		// if some previous portal can't see it, skip
		if (! (mightsee[pnum>>3] & (1<<(pnum&7)) ) )
			continue;

		// if this portal can see some portals we mightsee, recurse
		more = 0;
		for (j=0 ; j<portallongs ; j++)
		{
			((long *)newmight)[j] = ((long *)mightsee)[j] 
				& ((long *)p->portalflood)[j];
			more |= ((long *)newmight)[j] & ~((long *)cansee)[j];
		}

		if (!more)
			continue;	// can't see anything new

		cansee[pnum>>3] |= (1<<(pnum&7));

		RecursiveLeafBitFlow (p->leaf, newmight, cansee);
	}	
}