#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vec3w_t {int dummy; } ;
struct TYPE_2__ {struct vec3w_t accel; } ;

/* Variables and functions */
 TYPE_1__* wpaddata ; 

void WPAD_Accel(int chan, struct vec3w_t *accel)
{
	//if(chan<0 || chan>=WPAD_MAX_WIIMOTES || accel==NULL ) return;
	*accel = wpaddata[chan].accel;
}