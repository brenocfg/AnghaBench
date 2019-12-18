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
struct TYPE_4__ {int id; int (* Init ) () ;int /*<<< orphan*/  (* SetVolume ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* UnMuteAudio ) () ;int /*<<< orphan*/  (* MuteAudio ) () ;scalar_t__ Name; int /*<<< orphan*/  (* DeInit ) () ;} ;

/* Variables and functions */
 int SNDCORE_DEFAULT ; 
 TYPE_1__* SNDCore ; 
 TYPE_1__** SNDCoreList ; 
 TYPE_1__ SNDDummy ; 
 int /*<<< orphan*/  YAB_ERR_CANNOTINIT ; 
 int /*<<< orphan*/  YabSetError (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ scsp_mute_flags ; 
 int /*<<< orphan*/  scsp_volume ; 
 int /*<<< orphan*/  stub1 () ; 
 int stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 

int ScspChangeSoundCore(int coreid)
{
   int i;

   // Make sure the old core is freed
   if (SNDCore)
      SNDCore->DeInit();

   // If the default was requested, use the first core in the list
   if (coreid == SNDCORE_DEFAULT)
      SNDCore = SNDCoreList[0];
   else
   {
      // Otherwise, go through core list and find the id
      for (i = 0; SNDCoreList[i] != NULL; i++)
      {
         if (SNDCoreList[i]->id == coreid)
         {
            // Set to current core
            SNDCore = SNDCoreList[i];
            break;
         }
      }
   }

   if (SNDCore == NULL)
   {
      SNDCore = &SNDDummy;
      return -1;
   }

   if (SNDCore->Init() == -1)
   {
      // Since it failed, instead of it being fatal, we'll just use the dummy
      // core instead

      // This might be helpful though.
      YabSetError(YAB_ERR_CANNOTINIT, (void *)SNDCore->Name);

      SNDCore = &SNDDummy;
   }

   if (SNDCore)
   {
      if (scsp_mute_flags) SNDCore->MuteAudio();
      else SNDCore->UnMuteAudio();
      SNDCore->SetVolume(scsp_volume);
   }

   return 0;
}