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
struct TYPE_2__ {int* sh2irq_mask; int* regs; int /*<<< orphan*/ * sh2irqi; } ;
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  P32XI_CMD ; 
 TYPE_1__ Pico32x ; 
 int /*<<< orphan*/  p32x_update_irls (int /*<<< orphan*/ *,int) ; 

void p32x_update_cmd_irq(SH2 *sh2, int m68k_cycles)
{
  if ((Pico32x.sh2irq_mask[0] & 2) && (Pico32x.regs[2 / 2] & 1))
    Pico32x.sh2irqi[0] |= P32XI_CMD;
  else
    Pico32x.sh2irqi[0] &= ~P32XI_CMD;

  if ((Pico32x.sh2irq_mask[1] & 2) && (Pico32x.regs[2 / 2] & 2))
    Pico32x.sh2irqi[1] |= P32XI_CMD;
  else
    Pico32x.sh2irqi[1] &= ~P32XI_CMD;

  p32x_update_irls(sh2, m68k_cycles);
}