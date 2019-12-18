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
struct TYPE_5__ {int x; int y; int z; } ;
typedef  TYPE_1__ guVector ;

/* Variables and functions */

void c_guVecCross(guVector *a,guVector *b,guVector *axb)
{
	guVector vTmp;

	vTmp.x = (a->y*b->z)-(a->z*b->y);
	vTmp.y = (a->z*b->x)-(a->x*b->z);
	vTmp.z = (a->x*b->y)-(a->y*b->x);

	axb->x = vTmp.x;
	axb->y = vTmp.y;
	axb->z = vTmp.z;
}