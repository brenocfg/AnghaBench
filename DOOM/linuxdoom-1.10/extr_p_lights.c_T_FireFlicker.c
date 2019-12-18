#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count; int minlight; int maxlight; TYPE_1__* sector; } ;
typedef  TYPE_2__ fireflicker_t ;
struct TYPE_4__ {int lightlevel; } ;

/* Variables and functions */
 int P_Random () ; 

void T_FireFlicker (fireflicker_t* flick)
{
    int	amount;
	
    if (--flick->count)
	return;
	
    amount = (P_Random()&3)*16;
    
    if (flick->sector->lightlevel - amount < flick->minlight)
	flick->sector->lightlevel = flick->minlight;
    else
	flick->sector->lightlevel = flick->maxlight - amount;

    flick->count = 4;
}