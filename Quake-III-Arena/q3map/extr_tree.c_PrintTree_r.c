#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dist; int /*<<< orphan*/ * normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_9__ {size_t planenum; struct TYPE_9__** children; TYPE_4__* brushlist; } ;
typedef  TYPE_3__ node_t ;
struct TYPE_10__ {TYPE_1__* original; struct TYPE_10__* next; } ;
typedef  TYPE_4__ bspbrush_t ;
struct TYPE_7__ {int /*<<< orphan*/  brushnum; } ;

/* Variables and functions */
 size_t PLANENUM_LEAF ; 
 int /*<<< orphan*/  _printf (char*,...) ; 
 TYPE_2__* mapplanes ; 

void PrintTree_r (node_t *node, int depth)
{
	int		i;
	plane_t	*plane;
	bspbrush_t	*bb;

	for (i=0 ; i<depth ; i++)
		_printf ("  ");
	if (node->planenum == PLANENUM_LEAF)
	{
		if (!node->brushlist)
			_printf ("NULL\n");
		else
		{
			for (bb=node->brushlist ; bb ; bb=bb->next)
				_printf ("%i ", bb->original->brushnum);
			_printf ("\n");
		}
		return;
	}

	plane = &mapplanes[node->planenum];
	_printf ("#%i (%5.2f %5.2f %5.2f):%5.2f\n", node->planenum,
		plane->normal[0], plane->normal[1], plane->normal[2],
		plane->dist);
	PrintTree_r (node->children[0], depth+1);
	PrintTree_r (node->children[1], depth+1);
}