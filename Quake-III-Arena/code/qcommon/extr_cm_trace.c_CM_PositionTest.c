#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ allsolid; } ;
struct TYPE_9__ {TYPE_1__ trace; int /*<<< orphan*/ * size; int /*<<< orphan*/  start; } ;
typedef  TYPE_2__ traceWork_t ;
struct TYPE_10__ {int** bounds; int count; int maxcount; int* list; int /*<<< orphan*/  overflowed; scalar_t__ lastLeaf; int /*<<< orphan*/  storeLeafs; } ;
typedef  TYPE_3__ leafList_t ;
struct TYPE_11__ {int /*<<< orphan*/ * leafs; int /*<<< orphan*/  checkcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_BoxLeafnums_r (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CM_StoreLeafs ; 
 int /*<<< orphan*/  CM_TestInLeaf (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int MAX_POSITION_LEAFS ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_4__ cm ; 
 int /*<<< orphan*/  qfalse ; 

void CM_PositionTest( traceWork_t *tw ) {
	int		leafs[MAX_POSITION_LEAFS];
	int		i;
	leafList_t	ll;

	// identify the leafs we are touching
	VectorAdd( tw->start, tw->size[0], ll.bounds[0] );
	VectorAdd( tw->start, tw->size[1], ll.bounds[1] );

	for (i=0 ; i<3 ; i++) {
		ll.bounds[0][i] -= 1;
		ll.bounds[1][i] += 1;
	}

	ll.count = 0;
	ll.maxcount = MAX_POSITION_LEAFS;
	ll.list = leafs;
	ll.storeLeafs = CM_StoreLeafs;
	ll.lastLeaf = 0;
	ll.overflowed = qfalse;

	cm.checkcount++;

	CM_BoxLeafnums_r( &ll, 0 );


	cm.checkcount++;

	// test the contents of the leafs
	for (i=0 ; i < ll.count ; i++) {
		CM_TestInLeaf( tw, &cm.leafs[leafs[i]] );
		if ( tw->trace.allsolid ) {
			break;
		}
	}
}