#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* pc; } ;
struct TYPE_7__ {int pending; TYPE_1__* regs; } ;
struct TYPE_6__ {int h; int l; } ;
struct TYPE_5__ {TYPE_2__ byte; } ;

/* Variables and functions */
 int M68K_INT_ACK_AUTOVECTOR ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 TYPE_4__ s68k ; 
 int /*<<< orphan*/  s68k_update_irq (int) ; 
 TYPE_3__ scd ; 

int scd_68k_irq_ack(int level)
{
#ifdef LOG_SCD
  error("INT ack level %d  (%X)\n", level, s68k.pc);
#endif

#if 0
  /* level 5 interrupt is normally acknowledged by CDC */
  if (level != 5)
#endif
  {
    /* clear pending interrupt flag */
    scd.pending &= ~(1 << level);

    /* level 2 interrupt acknowledge */
    if (level == 2)
    {
      /* clear IFL2 flag */
      scd.regs[0x00].byte.h &= ~0x01;
    }

    /* update IRQ level */
    s68k_update_irq((scd.pending & scd.regs[0x32>>1].byte.l) >> 1);
  }

  return M68K_INT_ACK_AUTOVECTOR;
}