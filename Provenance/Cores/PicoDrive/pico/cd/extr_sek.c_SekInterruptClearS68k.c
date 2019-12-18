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
struct TYPE_4__ {int irq; } ;
struct TYPE_3__ {int* interrupts; } ;

/* Variables and functions */
 int CPU_INT_LEVEL ; 
 TYPE_2__ PicoCpuCS68k ; 
 TYPE_1__ PicoCpuFS68k ; 
 int new_irq_level (int) ; 

void SekInterruptClearS68k(int irq)
{
  int level_new = new_irq_level(irq);

#ifdef EMU_C68K
  PicoCpuCS68k.irq = level_new;
#endif
#ifdef EMU_M68K
  CPU_INT_LEVEL = level_new << 8;
#endif
#ifdef EMU_F68K
  PicoCpuFS68k.interrupts[0] = level_new;
#endif
}