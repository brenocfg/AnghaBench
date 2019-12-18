#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_3__ {int type; float dist; float* normal; int* children; } ;
typedef  TYPE_1__ tnode_t ;
typedef  int qboolean ;

/* Variables and functions */
#define  PLANE_X 130 
#define  PLANE_Y 129 
#define  PLANE_Z 128 
 int qfalse ; 
 int qtrue ; 
 TYPE_1__* tnodes ; 

qboolean PointInSolid_r( vec3_t start, int node ) {
	tnode_t	*tnode;
	float	front;

	while ( !(node & (1<<31) ) ) {
		tnode = &tnodes[node];
		switch (tnode->type) {
		case PLANE_X:
			front = start[0] - tnode->dist;
			break;
		case PLANE_Y:
			front = start[1] - tnode->dist;
			break;
		case PLANE_Z:
			front = start[2] - tnode->dist;
			break;
		default:
			front = (start[0]*tnode->normal[0] + start[1]*tnode->normal[1] + start[2]*tnode->normal[2]) - tnode->dist;
			break;
		}

		if ( front == 0 ) {
			// exactly on node, must check both sides
			return (qboolean) ( PointInSolid_r( start, tnode->children[0] ) 
				| PointInSolid_r( start, tnode->children[1] ) );
		}

		if ( front > 0 ) {
			node = tnode->children[0];
		} else {
			node = tnode->children[1];
		}
	}

	if ( node & ( 1 << 30 ) ) {
		return qtrue;
	}
	return qfalse;
}