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
struct TYPE_6__ {scalar_t__ planenum; struct TYPE_6__** children; TYPE_2__* faces; } ;
typedef  TYPE_1__ node_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ face_t ;

/* Variables and functions */
 int /*<<< orphan*/  FixFaceEdges (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ PLANENUM_LEAF ; 

void FixEdges_r (node_t *node)
{
	int		i;
	face_t	*f;

	if (node->planenum == PLANENUM_LEAF)
		return;

	for (f=node->faces ; f ; f=f->next)
		FixFaceEdges (node, f);

	for (i=0 ; i<2 ; i++)
		FixEdges_r (node->children[i]);
}