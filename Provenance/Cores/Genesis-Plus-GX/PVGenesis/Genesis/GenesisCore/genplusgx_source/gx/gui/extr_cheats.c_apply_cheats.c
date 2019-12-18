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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int romsize; scalar_t__ rom; } ;
struct TYPE_3__ {int address; scalar_t__ old; scalar_t__ data; scalar_t__* prev; scalar_t__ enable; } ;

/* Variables and functions */
 size_t MAX_CHEATS ; 
 int SYSTEM_MD ; 
 int SYSTEM_PBC ; 
 TYPE_2__ cart ; 
 int* cheatIndexes ; 
 TYPE_1__* cheatlist ; 
 size_t maxRAMcheats ; 
 size_t maxROMcheats ; 
 int maxcheats ; 
 int system_hw ; 
 scalar_t__** z80_readmap ; 

__attribute__((used)) static void apply_cheats(void)
{
  u8 *ptr;
  
  /* clear ROM&RAM patches counter */
  maxROMcheats = maxRAMcheats = 0;

  int i;
  for (i = 0; i < maxcheats; i++)
  {
    if (cheatlist[i].enable)
    {
      if (cheatlist[i].address < cart.romsize)
      {
        if ((system_hw & SYSTEM_PBC) == SYSTEM_MD)
        {
          /* patch ROM data */
          cheatlist[i].old = *(u16 *)(cart.rom + (cheatlist[i].address & 0xFFFFFE));
          *(u16 *)(cart.rom + (cheatlist[i].address & 0xFFFFFE)) = cheatlist[i].data;
        }
        else
        {
          /* add ROM patch */
          maxROMcheats++;
          cheatIndexes[MAX_CHEATS - maxROMcheats] = i;

          /* get current banked ROM address */
          ptr = &z80_readmap[(cheatlist[i].address) >> 10][cheatlist[i].address & 0x03FF];

          /* check if reference matches original ROM data */
          if (((u8)cheatlist[i].old) == *ptr)
          {
            /* patch data */
            *ptr = cheatlist[i].data;

            /* save patched ROM address */
            cheatlist[i].prev = ptr;
          }
          else
          {
            /* no patched ROM address yet */
            cheatlist[i].prev = NULL;
          }
        }
      }
      else if (cheatlist[i].address >= 0xFF0000)
      {
        /* add RAM patch */
        cheatIndexes[maxRAMcheats++] = i;
      }
    }
  }
}