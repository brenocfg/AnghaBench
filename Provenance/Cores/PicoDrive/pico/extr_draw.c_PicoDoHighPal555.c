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
struct TYPE_3__ {scalar_t__ dirtyPal; } ;
struct TYPE_4__ {scalar_t__ cram; TYPE_1__ m; } ;

/* Variables and functions */
 scalar_t__ HighPal ; 
 TYPE_2__ Pico ; 

void PicoDoHighPal555(int sh)
{
  unsigned int *spal, *dpal;
  unsigned int t, i;

  Pico.m.dirtyPal = 0;

  spal = (void *)Pico.cram;
  dpal = (void *)HighPal;

  for (i = 0; i < 0x40 / 2; i++) {
    t = spal[i];
#ifdef USE_BGR555
    t = ((t & 0x000e000e)<< 1) | ((t & 0x00e000e0)<<3) | ((t & 0x0e000e00)<<4);
#else
    t = ((t & 0x000e000e)<<12) | ((t & 0x00e000e0)<<3) | ((t & 0x0e000e00)>>7);
#endif
    // treat it like it was 4-bit per channel, since in s/h mode it somewhat is that.
    // otherwise intensity difference between this and s/h will be wrong
    t |= (t >> 4) & 0x08610861; // 0x18e318e3
    dpal[i] = t;
  }

  // norm: xxx0, sh: 0xxx, hi: 0xxx + 7
  if (sh)
  {
    // shadowed pixels
    for (i = 0; i < 0x40 / 2; i++)
      dpal[0x40/2 | i] = dpal[0xc0/2 | i] = (dpal[i] >> 1) & 0x738e738e;
    // hilighted pixels
    for (i = 0; i < 0x40 / 2; i++) {
      t = ((dpal[i] >> 1) & 0x738e738e) + 0x738e738e; // 0x7bef7bef;
      t |= (t >> 4) & 0x08610861;
      dpal[0x80/2 | i] = t;
    }
  }
}