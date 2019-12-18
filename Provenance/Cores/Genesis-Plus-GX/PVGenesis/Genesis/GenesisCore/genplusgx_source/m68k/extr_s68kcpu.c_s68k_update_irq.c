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
struct TYPE_2__ {char* cycles; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int CPU_INT_LEVEL ; 
 int /*<<< orphan*/  FLAG_INT_MASK ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int* irq_level ; 
 TYPE_1__ s68k ; 
 int /*<<< orphan*/  v_counter ; 

void s68k_update_irq(unsigned int mask)
{
  /* Get IRQ level (6 interrupt lines) */
  mask = irq_level[mask];

  /* Set IRQ level */
  CPU_INT_LEVEL = mask << 8;
  
#ifdef LOG_SCD
  error("[%d][%d] IRQ Level = %d(0x%02x) (%x)\n", v_counter, s68k.cycles, CPU_INT_LEVEL>>8,FLAG_INT_MASK,s68k.pc);
#endif
}