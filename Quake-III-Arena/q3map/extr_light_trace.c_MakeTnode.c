#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int planeNum; int* children; int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ tnode_t ;
struct TYPE_8__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ dplane_t ;
struct TYPE_9__ {int planeNum; int* children; } ;
typedef  TYPE_3__ dnode_t ;
struct TYPE_10__ {int cluster; } ;

/* Variables and functions */
 int /*<<< orphan*/  PlaneTypeForNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* dleafs ; 
 TYPE_3__* dnodes ; 
 TYPE_2__* dplanes ; 
 int tnode_p ; 
 int tnodes ; 

void MakeTnode (int nodenum)
{
	tnode_t			*t;
	dplane_t		*plane;
	int				i;
	dnode_t 		*node;
	int				leafNum;

	t = tnode_p++;

	node = dnodes + nodenum;
	plane = dplanes + node->planeNum;

	t->planeNum = node->planeNum;
	t->type = PlaneTypeForNormal( plane->normal );
	VectorCopy (plane->normal, t->normal);
	t->dist = plane->dist;
	
	for (i=0 ; i<2 ; i++)
	{
		if (node->children[i] < 0) {
			leafNum = -node->children[i] - 1;
			if ( dleafs[leafNum].cluster == -1  ) {
				// solid
				t->children[i] = leafNum | ( 1 << 31 ) | ( 1 << 30 );
			} else {
				t->children[i] = leafNum | ( 1 << 31 );
			}
		} else {
			t->children[i] = tnode_p - tnodes;
			MakeTnode (node->children[i]);
		}
	}
			
}