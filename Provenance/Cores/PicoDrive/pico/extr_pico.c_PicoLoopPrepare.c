#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pal; int dirtyPal; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 int PicoRegionOverride ; 
 int rendstatus_old ; 
 int scanlines_total ; 

void PicoLoopPrepare(void)
{
  if (PicoRegionOverride)
    // force setting possibly changed..
    Pico.m.pal = (PicoRegionOverride == 2 || PicoRegionOverride == 8) ? 1 : 0;

  // FIXME: PAL has 313 scanlines..
  scanlines_total = Pico.m.pal ? 312 : 262;

  Pico.m.dirtyPal = 1;
  rendstatus_old = -1;
}