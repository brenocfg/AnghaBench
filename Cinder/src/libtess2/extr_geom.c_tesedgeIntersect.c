#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int s; int t; } ;
typedef  TYPE_1__ TESSvertex ;
typedef  int /*<<< orphan*/  TESSreal ;

/* Variables and functions */
 int /*<<< orphan*/  EdgeEval (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  EdgeSign (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 void* Interpolate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Swap (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TransEval (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ TransLeq (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TransSign (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ VertLeq (TYPE_1__*,TYPE_1__*) ; 

void tesedgeIntersect( TESSvertex *o1, TESSvertex *d1,
					  TESSvertex *o2, TESSvertex *d2,
					  TESSvertex *v )
					  /* Given edges (o1,d1) and (o2,d2), compute their point of intersection.
					  * The computed point is guaranteed to lie in the intersection of the
					  * bounding rectangles defined by each edge.
					  */
{
	TESSreal z1, z2;

	/* This is certainly not the most efficient way to find the intersection
	* of two line segments, but it is very numerically stable.
	*
	* Strategy: find the two middle vertices in the VertLeq ordering,
	* and interpolate the intersection s-value from these.  Then repeat
	* using the TransLeq ordering to find the intersection t-value.
	*/

	if( ! VertLeq( o1, d1 )) { Swap( o1, d1 ); }
	if( ! VertLeq( o2, d2 )) { Swap( o2, d2 ); }
	if( ! VertLeq( o1, o2 )) { Swap( o1, o2 ); Swap( d1, d2 ); }

	if( ! VertLeq( o2, d1 )) {
		/* Technically, no intersection -- do our best */
		v->s = (o2->s + d1->s) / 2;
	} else if( VertLeq( d1, d2 )) {
		/* Interpolate between o2 and d1 */
		z1 = EdgeEval( o1, o2, d1 );
		z2 = EdgeEval( o2, d1, d2 );
		if( z1+z2 < 0 ) { z1 = -z1; z2 = -z2; }
		v->s = Interpolate( z1, o2->s, z2, d1->s );
	} else {
		/* Interpolate between o2 and d2 */
		z1 = EdgeSign( o1, o2, d1 );
		z2 = -EdgeSign( o1, d2, d1 );
		if( z1+z2 < 0 ) { z1 = -z1; z2 = -z2; }
		v->s = Interpolate( z1, o2->s, z2, d2->s );
	}

	/* Now repeat the process for t */

	if( ! TransLeq( o1, d1 )) { Swap( o1, d1 ); }
	if( ! TransLeq( o2, d2 )) { Swap( o2, d2 ); }
	if( ! TransLeq( o1, o2 )) { Swap( o1, o2 ); Swap( d1, d2 ); }

	if( ! TransLeq( o2, d1 )) {
		/* Technically, no intersection -- do our best */
		v->t = (o2->t + d1->t) / 2;
	} else if( TransLeq( d1, d2 )) {
		/* Interpolate between o2 and d1 */
		z1 = TransEval( o1, o2, d1 );
		z2 = TransEval( o2, d1, d2 );
		if( z1+z2 < 0 ) { z1 = -z1; z2 = -z2; }
		v->t = Interpolate( z1, o2->t, z2, d1->t );
	} else {
		/* Interpolate between o2 and d2 */
		z1 = TransSign( o1, o2, d1 );
		z2 = -TransSign( o1, d2, d1 );
		if( z1+z2 < 0 ) { z1 = -z1; z2 = -z2; }
		v->t = Interpolate( z1, o2->t, z2, d2->t );
	}
}