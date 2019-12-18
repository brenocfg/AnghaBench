#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int isdiskchanged; int /*<<< orphan*/  status; TYPE_1__* cdi; } ;
struct TYPE_4__ {int id; scalar_t__ (* Init ) (char const*) ;scalar_t__ Name; int /*<<< orphan*/  (* DeInit ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDB_STAT_PAUSE ; 
 int CDCORE_DEFAULT ; 
 TYPE_1__** CDCoreList ; 
 TYPE_2__* Cs2Area ; 
 TYPE_1__ DummyCD ; 
 int /*<<< orphan*/  SmpcRecheckRegion () ; 
 int /*<<< orphan*/  YAB_ERR_CANNOTINIT ; 
 int /*<<< orphan*/  YabSetError (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ stub2 (char const*) ; 

int Cs2ChangeCDCore(int coreid, const char *cdpath)
{
   int i;

   // Make sure the old core is freed
   if (Cs2Area->cdi != NULL)
      Cs2Area->cdi->DeInit();

   // So which core do we want?
   if (coreid == CDCORE_DEFAULT)
      coreid = 0; // Assume we want the first one

   // Go through core list and find the id
   for (i = 0; CDCoreList[i] != NULL; i++)
   {
      if (CDCoreList[i]->id == coreid)
      {
         // Set to current core
         Cs2Area->cdi = CDCoreList[i];
         break;
      }
   }

   if (Cs2Area->cdi == NULL)
   {
      Cs2Area->cdi = &DummyCD;
      return -1;
   }

   if (Cs2Area->cdi->Init(cdpath) != 0)
   {
      // This might be helpful.
      YabSetError(YAB_ERR_CANNOTINIT, (void *)Cs2Area->cdi->Name);

      // Since it failed, instead of it being fatal, we'll just use the dummy
      // core instead
      Cs2Area->cdi = &DummyCD;
   }

   Cs2Area->isdiskchanged = 1;
   Cs2Area->status = CDB_STAT_PAUSE;
   SmpcRecheckRegion();

   return 0;
}