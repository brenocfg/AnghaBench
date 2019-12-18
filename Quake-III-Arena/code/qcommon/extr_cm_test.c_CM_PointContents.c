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
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_12__ {int numLeafBrushes; int firstLeafBrush; } ;
struct TYPE_10__ {TYPE_5__ leaf; } ;
typedef  TYPE_3__ cmodel_t ;
typedef  scalar_t__ clipHandle_t ;
struct TYPE_11__ {int numsides; int contents; TYPE_2__* sides; } ;
typedef  TYPE_4__ cbrush_t ;
typedef  TYPE_5__ cLeaf_t ;
struct TYPE_13__ {int* leafbrushes; TYPE_4__* brushes; TYPE_5__* leafs; int /*<<< orphan*/  numNodes; } ;
struct TYPE_9__ {TYPE_1__* plane; } ;
struct TYPE_8__ {float dist; int /*<<< orphan*/  normal; } ;

/* Variables and functions */
 TYPE_3__* CM_ClipHandleToModel (scalar_t__) ; 
 int CM_PointLeafnum_r (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 float DotProduct (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 TYPE_6__ cm ; 

int CM_PointContents( const vec3_t p, clipHandle_t model ) {
	int			leafnum;
	int			i, k;
	int			brushnum;
	cLeaf_t		*leaf;
	cbrush_t	*b;
	int			contents;
	float		d;
	cmodel_t	*clipm;

	if (!cm.numNodes) {	// map not loaded
		return 0;
	}

	if ( model ) {
		clipm = CM_ClipHandleToModel( model );
		leaf = &clipm->leaf;
	} else {
		leafnum = CM_PointLeafnum_r (p, 0);
		leaf = &cm.leafs[leafnum];
	}

	contents = 0;
	for (k=0 ; k<leaf->numLeafBrushes ; k++) {
		brushnum = cm.leafbrushes[leaf->firstLeafBrush+k];
		b = &cm.brushes[brushnum];

		// see if the point is in the brush
		for ( i = 0 ; i < b->numsides ; i++ ) {
			d = DotProduct( p, b->sides[i].plane->normal );
// FIXME test for Cash
//			if ( d >= b->sides[i].plane->dist ) {
			if ( d > b->sides[i].plane->dist ) {
				break;
			}
		}

		if ( i == b->numsides ) {
			contents |= b->contents;
		}
	}

	return contents;
}