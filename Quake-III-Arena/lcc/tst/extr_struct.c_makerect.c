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
struct TYPE_5__ {void* pt2; void* pt1; } ;
typedef  TYPE_1__ rect ;
typedef  void* point ;

/* Variables and functions */
 TYPE_1__ canonrect (TYPE_1__) ; 

rect makerect(point p1, point p2) {	/* make a rectangle from two points */
	rect r;

	r.pt1 = p1;
	r.pt2 = p2;
	return canonrect(r);
}