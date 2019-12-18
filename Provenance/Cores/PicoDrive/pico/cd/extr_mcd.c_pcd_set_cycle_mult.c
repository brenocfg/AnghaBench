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
struct TYPE_3__ {scalar_t__ pal; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 unsigned long long mcd_m68k_cycle_mult ; 

__attribute__((used)) static void pcd_set_cycle_mult(void)
{
  // ~1.63 for NTSC, ~1.645 for PAL
  if (Pico.m.pal)
    mcd_m68k_cycle_mult = ((12500000ull << 16) / (50*312*488));
  else
    mcd_m68k_cycle_mult = ((12500000ull << 16) / (60*262*488)) + 1;
}