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
struct TYPE_3__ {double hi; double lo; } ;
typedef  TYPE_1__ INTERVAL ;

/* Variables and functions */

__attribute__((used)) static INTERVAL
hilo(double a, double b, double c, double d)
{
    /*  returns  the  smallest  interval  containing  a,  b,  c,  and  d  */
    /*  used  by  *,  /  routines  */
    INTERVAL v;

    if (a > b)
    {
	v.hi = a;
	v.lo = b;
    }
    else
    {
	v.hi = b;
	v.lo = a;
    }

    if (c > d)
    {
	if (c > v.hi)
	    v.hi = c;
	if (d < v.lo)
	    v.lo = d;
    }
    else
    {
	if (d > v.hi)
	    v.hi = d;
	if (c < v.lo)
	    v.lo = c;
    }
    return (v);
}