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
struct TYPE_4__ {scalar_t__ planenum; scalar_t__ volume; int /*<<< orphan*/  brushlist; struct TYPE_4__** children; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBrush (scalar_t__) ; 
 int /*<<< orphan*/  FreeBrushList (int /*<<< orphan*/ ) ; 
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  c_nodes ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int numthreads ; 

void FreeTree_r (node_t *node)
{
	// free children
	if (node->planenum != PLANENUM_LEAF)
	{
		FreeTree_r (node->children[0]);
		FreeTree_r (node->children[1]);
	}

	// free bspbrushes
	FreeBrushList (node->brushlist);

	// free the node
	if (node->volume)
		FreeBrush (node->volume);

	if (numthreads == 1)
		c_nodes--;
	free (node);
}