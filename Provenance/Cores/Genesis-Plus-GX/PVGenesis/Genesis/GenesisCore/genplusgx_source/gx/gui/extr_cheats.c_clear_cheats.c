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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int romsize; scalar_t__ rom; } ;
struct TYPE_3__ {int address; int /*<<< orphan*/ * prev; int /*<<< orphan*/  old; scalar_t__ enable; } ;

/* Variables and functions */
 int SYSTEM_MD ; 
 int SYSTEM_PBC ; 
 TYPE_2__ cart ; 
 TYPE_1__* cheatlist ; 
 int maxcheats ; 
 int system_hw ; 

__attribute__((used)) static void clear_cheats(void)
{
  int i = maxcheats;

  /* disable cheats in reversed order in case the same address is used by multiple patches */
  while (i > 0)
  {
    if (cheatlist[i-1].enable)
    {
      if (cheatlist[i-1].address < cart.romsize)
      {
        if ((system_hw & SYSTEM_PBC) == SYSTEM_MD)
        {
          /* restore original ROM data */
          *(u16 *)(cart.rom + (cheatlist[i-1].address & 0xFFFFFE)) = cheatlist[i-1].old;
        }
        else
        {
          /* check if previous banked ROM address has been patched */
          if (cheatlist[i-1].prev != NULL)
          {
            /* restore original data */
            *cheatlist[i-1].prev = cheatlist[i-1].old;

            /* no more patched ROM address */
            cheatlist[i-1].prev = NULL;
          }
        }
      }
    }

    i--;
  }
}