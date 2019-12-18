#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_7__ {size_t numOpenLeafs; int* openLeafNumbers; TYPE_1__* trace; } ;
typedef  TYPE_2__ traceWork_t ;
struct TYPE_8__ {int type; float dist; float* normal; int* children; } ;
typedef  TYPE_3__ tnode_t ;
struct TYPE_6__ {int passSolid; int /*<<< orphan*/  hit; } ;

/* Variables and functions */
 size_t MAX_MAP_LEAFS ; 
#define  PLANE_X 130 
#define  PLANE_Y 129 
#define  PLANE_Z 128 
 float TRACE_ON_EPSILON ; 
 int /*<<< orphan*/  VectorCopy (float* const,int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int qtrue ; 
 TYPE_3__* tnodes ; 

int TraceLine_r( int node, const vec3_t start, const vec3_t stop, traceWork_t *tw ) {
	tnode_t	*tnode;
	float	front, back;
	vec3_t	mid;
	float	frac;
	int		side;
	int		r;

	if (node & (1<<31)) {
		if (node & ( 1 << 30 ) ) {
			VectorCopy (start, tw->trace->hit);
			tw->trace->passSolid = qtrue;
			return qtrue;
		} else {
			// save the node off for more exact testing
			if ( tw->numOpenLeafs == MAX_MAP_LEAFS ) {
				return qfalse;
			}
			tw->openLeafNumbers[ tw->numOpenLeafs ] = node & ~(3 << 30);
			tw->numOpenLeafs++;
			return qfalse;
		}
	}

	tnode = &tnodes[node];
	switch (tnode->type) {
	case PLANE_X:
		front = start[0] - tnode->dist;
		back = stop[0] - tnode->dist;
		break;
	case PLANE_Y:
		front = start[1] - tnode->dist;
		back = stop[1] - tnode->dist;
		break;
	case PLANE_Z:
		front = start[2] - tnode->dist;
		back = stop[2] - tnode->dist;
		break;
	default:
		front = (start[0]*tnode->normal[0] + start[1]*tnode->normal[1] + start[2]*tnode->normal[2]) - tnode->dist;
		back = (stop[0]*tnode->normal[0] + stop[1]*tnode->normal[1] + stop[2]*tnode->normal[2]) - tnode->dist;
		break;
	}

	if (front >= -TRACE_ON_EPSILON && back >= -TRACE_ON_EPSILON) {
		return TraceLine_r (tnode->children[0], start, stop, tw);
	}
	
	if (front < TRACE_ON_EPSILON && back < TRACE_ON_EPSILON) {
		return TraceLine_r (tnode->children[1], start, stop, tw);
	}

	side = front < 0;
	
	frac = front / (front-back);

	mid[0] = start[0] + (stop[0] - start[0])*frac;
	mid[1] = start[1] + (stop[1] - start[1])*frac;
	mid[2] = start[2] + (stop[2] - start[2])*frac;

	r = TraceLine_r (tnode->children[side], start, mid, tw);

	if (r) {
		return r;
	}

//	trace->planeNum = tnode->planeNum;
	return TraceLine_r (tnode->children[!side], mid, stop, tw);
}