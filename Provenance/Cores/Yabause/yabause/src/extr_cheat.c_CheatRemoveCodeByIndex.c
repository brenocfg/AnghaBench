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
typedef  int /*<<< orphan*/  cheatlist_struct ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEATTYPE_NONE ; 
 TYPE_1__* cheatlist ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int numcheats ; 

int CheatRemoveCodeByIndex(int i)
{
   // If there's a description, free the memory.
   if (cheatlist[i].desc)
   {
      free(cheatlist[i].desc);
      cheatlist[i].desc = NULL;
   }

   // Move all entries one forward
   for (; i < numcheats-1; i++)
      memcpy(&cheatlist[i], &cheatlist[i+1], sizeof(cheatlist_struct));

   numcheats--;

   // Set the last one to type none
   cheatlist[numcheats].type = CHEATTYPE_NONE;

   return 0;
}