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
struct TYPE_2__ {unsigned int sh2irqs; unsigned int* sh2irqi; int* sh2irq_mask; } ;
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 unsigned int P32XI_VRES ; 
 TYPE_1__ Pico32x ; 
 int /*<<< orphan*/  p32x_update_irls (int /*<<< orphan*/ *,int) ; 

void p32x_trigger_irq(SH2 *sh2, int m68k_cycles, unsigned int mask)
{
  Pico32x.sh2irqs |= mask & P32XI_VRES;
  Pico32x.sh2irqi[0] |= mask & (Pico32x.sh2irq_mask[0] << 3);
  Pico32x.sh2irqi[1] |= mask & (Pico32x.sh2irq_mask[1] << 3);

  p32x_update_irls(sh2, m68k_cycles);
}