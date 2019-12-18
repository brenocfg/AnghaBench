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
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {scalar_t__ rom; } ;
struct TYPE_3__ {int* regs; int /*<<< orphan*/ * old; scalar_t__* addr; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 TYPE_2__ cart ; 
 TYPE_1__ ggenie ; 

void ggenie_switch(int enable)
{
  int i;
  if (enable)
  {
    /* enable cheats */
    for (i=0; i<6; i++)
    {
      /* patch is enabled ? */
      if (ggenie.regs[0] & (1 << i))
      {
        /* save old value and patch ROM if enabled */
        ggenie.old[i] = *(uint16 *)(cart.rom + ggenie.addr[i]);
        *(uint16 *)(cart.rom + ggenie.addr[i]) = ggenie.data[i];
      }
    }
  }
  else
  {
    /* disable cheats in reversed order in case the same address is used by multiple patches */
    for (i=5; i>=0; i--)
    {
      /* patch is enabled ? */
      if (ggenie.regs[0] & (1 << i))
      {
        /* restore original ROM value */
        *(uint16 *)(cart.rom + ggenie.addr[i]) = ggenie.old[i];
      }
    }
  }
}