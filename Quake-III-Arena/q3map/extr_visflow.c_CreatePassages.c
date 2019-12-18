#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int numpoints; int /*<<< orphan*/ * points; } ;
typedef  TYPE_1__ winding_t ;
struct TYPE_20__ {size_t leaf; int* portalflood; float radius; TYPE_1__* winding; int /*<<< orphan*/  origin; scalar_t__ removed; TYPE_4__* passages; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ vportal_t ;
struct TYPE_21__ {float dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ plane_t ;
struct TYPE_22__ {int* cansee; struct TYPE_22__* next; } ;
typedef  TYPE_4__ passage_t ;
struct TYPE_23__ {int numportals; TYPE_2__** portals; } ;
typedef  TYPE_5__ leaf_t ;

/* Variables and functions */
 int AddSeperators (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_SEPERATORS ; 
 float ON_EPSILON ; 
 TYPE_1__* PassageChopWinding (TYPE_1__*,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  _printf (char*,int) ; 
 TYPE_5__* leafs ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int numportals ; 
 scalar_t__ portalbytes ; 
 TYPE_2__* portals ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__** sorted_portals ; 
 int /*<<< orphan*/  stat_done ; 

void CreatePassages(int portalnum)
{
	int i, j, k, n, numseperators, numsee;
	float d;
	vportal_t *portal, *p, *target;
	leaf_t *leaf;
	passage_t	*passage, *lastpassage;
	plane_t seperators[MAX_SEPERATORS*2];
	winding_t *w;
	winding_t in, out, *res;

#ifdef MREDEBUG
	_printf("\r%6d", portalnum);
#endif

	portal = sorted_portals[portalnum];

	if (portal->removed)
	{
		portal->status = stat_done;
		return;
	}

	lastpassage = NULL;
	leaf = &leafs[portal->leaf];
	for (i = 0; i < leaf->numportals; i++)
	{
		target = leaf->portals[i];
		if (target->removed)
			continue;

		passage = (passage_t *) malloc(sizeof(passage_t) + portalbytes);
		memset(passage, 0, sizeof(passage_t) + portalbytes);
		numseperators = AddSeperators(portal->winding, target->winding, qfalse, seperators, MAX_SEPERATORS*2);
		numseperators += AddSeperators(target->winding, portal->winding, qtrue, &seperators[numseperators], MAX_SEPERATORS*2-numseperators);

		passage->next = NULL;
		if (lastpassage)
			lastpassage->next = passage;
		else
			portal->passages = passage;
		lastpassage = passage;

		numsee = 0;
		//create the passage->cansee
		for (j = 0; j < numportals * 2; j++)
		{
			p = &portals[j];
			if (p->removed)
				continue;
			if ( ! (target->portalflood[j >> 3] & (1<<(j&7)) ) )
				continue;
			if ( ! (portal->portalflood[j >> 3] & (1<<(j&7)) ) )
				continue;
			for (k = 0; k < numseperators; k++)
			{
				//
				d = DotProduct (p->origin, seperators[k].normal) - seperators[k].dist;
				//if completely at the back of the seperator plane
				if (d < -p->radius + ON_EPSILON)
					break;
				w = p->winding;
				for (n = 0; n < w->numpoints; n++)
				{
					d = DotProduct (w->points[n], seperators[k].normal) - seperators[k].dist;
					//if at the front of the seperator
					if (d > ON_EPSILON)
						break;
				}
				//if no points are at the front of the seperator
				if (n >= w->numpoints)
					break;
			}
			if (k < numseperators)
				continue;
			memcpy(&in, p->winding, sizeof(winding_t));
			for (k = 0; k < numseperators; k++)
			{
				res = PassageChopWinding(&in, &out, &seperators[k]);
				if (res == &out)
					memcpy(&in, &out, sizeof(winding_t));
				if (res == NULL)
					break;
			}
			if (k < numseperators)
				continue;
			passage->cansee[j >> 3] |= (1<<(j&7));
			numsee++;
		}
	}
}