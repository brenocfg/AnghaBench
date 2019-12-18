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

void c_guQuatInverse(guQuaternion *a,guQuaternion *d)
{
	f32 mag,nrminv;

	mag = (a->x*a->x) + (a->y*a->y) + (a->z*a->z) + (a->w*a->w);
	if(mag==0.0f) mag = 1.0f;

	nrminv = 1.0f/mag;
	d->x = -a->x*nrminv;
	d->y = -a->y*nrminv;
	d->z = -a->z*nrminv;
	d->w =  a->w*nrminv;
}