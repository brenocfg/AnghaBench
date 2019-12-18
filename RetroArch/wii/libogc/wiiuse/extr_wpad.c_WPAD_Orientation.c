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
struct orient_t {int dummy; } ;
struct TYPE_2__ {struct orient_t orient; } ;

/* Variables and functions */
 TYPE_1__* wpaddata ; 

void WPAD_Orientation(int chan, struct orient_t *orient)
{
	//if(chan<0 || chan>=WPAD_MAX_WIIMOTES || orient==NULL ) return;
	*orient = wpaddata[chan].orient;
}