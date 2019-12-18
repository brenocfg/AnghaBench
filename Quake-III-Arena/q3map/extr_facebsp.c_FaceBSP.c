#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_6__* headnode; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_12__ {TYPE_1__* w; struct TYPE_12__* next; } ;
typedef  TYPE_3__ bspface_t ;
struct TYPE_13__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
struct TYPE_10__ {int numpoints; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* AllocNode () ; 
 TYPE_2__* AllocTree () ; 
 int /*<<< orphan*/  BuildFaceTree_r (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int c_faceLeafs ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 

tree_t *FaceBSP( bspface_t *list ) {
	tree_t		*tree;
	bspface_t	*face;
	int			i;
	int			count;

	qprintf( "--- FaceBSP ---\n" );

	tree = AllocTree ();

	count = 0;
	for ( face = list ; face ; face = face->next ) {
		count++;
		for ( i = 0 ; i < face->w->numpoints ; i++ ) {
			AddPointToBounds( face->w->p[i], tree->mins, tree->maxs);
		}
	}
	qprintf( "%5i faces\n", count );

	tree->headnode = AllocNode();
	VectorCopy( tree->mins, tree->headnode->mins );
	VectorCopy( tree->maxs, tree->headnode->maxs );
	c_faceLeafs = 0;

	BuildFaceTree_r ( tree->headnode, list );

	qprintf( "%5i leafs\n", c_faceLeafs );

	return tree;
}