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
struct gforce_t {int dummy; } ;
struct TYPE_2__ {struct gforce_t gforce; } ;

/* Variables and functions */
 TYPE_1__* wpaddata ; 

void WPAD_GForce(int chan, struct gforce_t *gforce)
{
	//if(chan<0 || chan>=WPAD_MAX_WIIMOTES || gforce==NULL ) return;
	*gforce = wpaddata[chan].gforce;
}