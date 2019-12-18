#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int id; scalar_t__ (* Init ) () ;int /*<<< orphan*/  (* Vdp1Reset ) () ;} ;

/* Variables and functions */
 int VIDCORE_DEFAULT ; 
 TYPE_1__* VIDCore ; 
 TYPE_1__** VIDCoreList ; 
 scalar_t__ Vdp2Regs ; 
 int /*<<< orphan*/  VideoDeInit () ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

int VideoChangeCore(int coreid)
{
   int i;

   // Make sure the old core is freed
   VideoDeInit();

   // So which core do we want?
   if (coreid == VIDCORE_DEFAULT)
      coreid = 0; // Assume we want the first one

   // Go through core list and find the id
   for (i = 0; VIDCoreList[i] != NULL; i++)
   {
      if (VIDCoreList[i]->id == coreid)
      {
         // Set to current core
         VIDCore = VIDCoreList[i];
         break;
      }
   }

   if (VIDCore == NULL)
      return -1;

   if (VIDCore->Init() != 0)
      return -1;

   // Reset resolution/priority variables
   if (Vdp2Regs)
   {
      VIDCore->Vdp1Reset();
   }

   return 0;
}