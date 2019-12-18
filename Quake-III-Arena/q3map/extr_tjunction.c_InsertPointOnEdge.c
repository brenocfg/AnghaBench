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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_6__ {float intercept; struct TYPE_6__* prev; struct TYPE_6__* next; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_1__ edgePoint_t ;
struct TYPE_7__ {TYPE_1__ chain; int /*<<< orphan*/  dir; int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ edgeLine_t ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float LINE_POSITION_EPSILON ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 

void InsertPointOnEdge( vec3_t v, edgeLine_t *e ) {
	vec3_t		delta;
	float		d;
	edgePoint_t	*p, *scan;

	VectorSubtract( v, e->origin, delta );
	d = DotProduct( delta, e->dir );

	p = malloc( sizeof(edgePoint_t) );
	p->intercept = d;
	VectorCopy( v, p->xyz );

	if ( e->chain.next == &e->chain ) {
		e->chain.next = e->chain.prev = p;
		p->next = p->prev = &e->chain;
		return;
	}

	scan = e->chain.next;
	for ( ; scan != &e->chain ; scan = scan->next ) {
		d = p->intercept - scan->intercept;
		if ( d > -LINE_POSITION_EPSILON && d < LINE_POSITION_EPSILON ) {
			free( p );
			return;		// the point is already set
		}

		if ( p->intercept < scan->intercept ) {
			// insert here
			p->prev = scan->prev;
			p->next = scan;
			scan->prev->next = p;
			scan->prev = p;
			return;
		}
	}

	// add at the end
	p->prev = scan->prev;
	p->next = scan;
	scan->prev->next = p;
	scan->prev = p;
}