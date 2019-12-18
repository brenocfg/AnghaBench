#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ s; scalar_t__ t; } ;
typedef  TYPE_1__ TESSvertex ;
typedef  scalar_t__ TESSreal ;

/* Variables and functions */
 scalar_t__ VertLeq (TYPE_1__*,TYPE_1__*) ; 

TESSreal tesedgeSign( TESSvertex *u, TESSvertex *v, TESSvertex *w )
{
	/* Returns a number whose sign matches EdgeEval(u,v,w) but which
	* is cheaper to evaluate.  Returns > 0, == 0 , or < 0
	* as v is above, on, or below the edge uw.
	*/
	TESSreal gapL, gapR;

//	assert( VertLeq( u, v ) && VertLeq( v, w ));
	if( ! ( VertLeq( u, v ) && VertLeq( v, w )) )
		return 0;// this is incorrect but prevents a crash with pernicious geometry

	gapL = v->s - u->s;
	gapR = w->s - v->s;

	if( gapL + gapR > 0 ) {
		return (v->t - w->t) * gapL + (v->t - u->t) * gapR;
	}
	/* vertical line */
	return 0;
}