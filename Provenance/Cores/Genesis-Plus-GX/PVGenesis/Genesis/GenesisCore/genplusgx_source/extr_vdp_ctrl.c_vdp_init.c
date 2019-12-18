#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int SYSTEM_MD ; 
 int SYSTEM_PBC ; 
 int lines_per_frame ; 
 void* m68k_set_irq ; 
 void* m68k_set_irq_delay ; 
 void* set_irq_line ; 
 void* set_irq_line_delay ; 
 int system_hw ; 
 scalar_t__ vdp_pal ; 
 void* z80_set_irq_line ; 

void vdp_init(void)
{
  /* PAL/NTSC timings */
  lines_per_frame = vdp_pal ? 313: 262;

  /* CPU interrupt line(s)*/
  if ((system_hw & SYSTEM_PBC) == SYSTEM_MD)
  {
    /* 68k cpu */
    set_irq_line = m68k_set_irq;
    set_irq_line_delay = m68k_set_irq_delay;
  }
  else
  {
    /* Z80 cpu */
    set_irq_line = z80_set_irq_line;
    set_irq_line_delay = z80_set_irq_line;
  }
}