#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float x; float y; float z; float w; } ;
typedef  TYPE_1__ guQuaternion ;
typedef  float f32 ;

/* Variables and functions */
 float sqrtf (float) ; 

void c_guQuatNormalize(guQuaternion *a,guQuaternion *d)
{
	f32 dot,scale;

	dot = (a->x*a->x) + (a->y*a->y) + (a->z*a->z) + (a->w*a->w);
	if(dot==0.0f) d->x = d->y = d->z = d->w = 0.0f;
	else {
		scale = 1.0f/sqrtf(dot);
		d->x = a->x*scale;
		d->y = a->y*scale;
		d->z = a->z*scale;
		d->w = a->w*scale;
	}
}