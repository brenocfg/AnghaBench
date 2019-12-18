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
struct TYPE_5__ {int count; scalar_t__ maxlight; scalar_t__ minlight; int mintime; int maxtime; TYPE_1__* sector; } ;
typedef  TYPE_2__ lightflash_t ;
struct TYPE_4__ {scalar_t__ lightlevel; } ;

/* Variables and functions */
 int P_Random () ; 

void T_LightFlash (lightflash_t* flash)
{
    if (--flash->count)
	return;
	
    if (flash->sector->lightlevel == flash->maxlight)
    {
	flash-> sector->lightlevel = flash->minlight;
	flash->count = (P_Random()&flash->mintime)+1;
    }
    else
    {
	flash-> sector->lightlevel = flash->maxlight;
	flash->count = (P_Random()&flash->maxtime)+1;
    }

}