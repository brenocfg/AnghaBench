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
struct TYPE_3__ {int x; int y; int z; } ;
typedef  TYPE_1__ guVector ;
typedef  int f32 ;

/* Variables and functions */
 int sqrtf (int) ; 

void c_guVecNormalize(guVector *v)
{
	f32 m;

	m = ((v->x)*(v->x)) + ((v->y)*(v->y)) + ((v->z)*(v->z));
	m = 1/sqrtf(m);
	v->x *= m;
	v->y *= m;
	v->z *= m;
}