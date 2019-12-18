#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int s; int t; } ;
typedef  TYPE_1__ TESSvertex ;

/* Variables and functions */

int tesvertCCW( TESSvertex *u, TESSvertex *v, TESSvertex *w )
{
	/* For almost-degenerate situations, the results are not reliable.
	* Unless the floating-point arithmetic can be performed without
	* rounding errors, *any* implementation will give incorrect results
	* on some degenerate inputs, so the client must have some way to
	* handle this situation.
	*/
	return (u->s*(v->t - w->t) + v->s*(w->t - u->t) + w->s*(u->t - v->t)) >= 0;
}