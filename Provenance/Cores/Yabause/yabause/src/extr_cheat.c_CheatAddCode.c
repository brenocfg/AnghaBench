#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  int /*<<< orphan*/  cheatlist_struct ;
struct TYPE_4__ {int type; int enable; int /*<<< orphan*/ * desc; void* val; void* addr; } ;

/* Variables and functions */
 int CHEATTYPE_NONE ; 
 TYPE_1__* cheatlist ; 
 size_t cheatsize ; 
 size_t numcheats ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 

int CheatAddCode(int type, u32 addr, u32 val)
{
   if (cheatlist == NULL)
      return -1;

   cheatlist[numcheats].type = type;
   cheatlist[numcheats].addr = addr;
   cheatlist[numcheats].val = val;
   cheatlist[numcheats].desc = NULL;
   cheatlist[numcheats].enable = 1;
   numcheats++;

   // Make sure we still have room
   if (numcheats >= cheatsize)
   {
      cheatlist = realloc(cheatlist, sizeof(cheatlist_struct) * (cheatsize * 2));
      cheatsize *= 2;
   }

   cheatlist[numcheats].type = CHEATTYPE_NONE;

   return 0;
}