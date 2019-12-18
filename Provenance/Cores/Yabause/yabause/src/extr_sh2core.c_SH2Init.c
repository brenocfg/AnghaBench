#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int id; scalar_t__ (* Init ) () ;} ;
struct TYPE_9__ {int BCR1; } ;
struct TYPE_10__ {int isslave; TYPE_1__ onchip; } ;
typedef  TYPE_2__ SH2_struct ;

/* Variables and functions */
 TYPE_2__* MSH2 ; 
 int SH2CORE_DEFAULT ; 
 TYPE_6__* SH2Core ; 
 TYPE_6__** SH2CoreList ; 
 scalar_t__ SH2TrackInfLoopInit (TYPE_2__*) ; 
 TYPE_2__* SSH2 ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ stub1 () ; 

int SH2Init(int coreid)
{
   int i;

   // MSH2
   if ((MSH2 = (SH2_struct *)calloc(1, sizeof(SH2_struct))) == NULL)
      return -1;

   if (SH2TrackInfLoopInit(MSH2) != 0)
      return -1;

   MSH2->onchip.BCR1 = 0x0000;
   MSH2->isslave = 0;

   // SSH2
   if ((SSH2 = (SH2_struct *)calloc(1, sizeof(SH2_struct))) == NULL)
      return -1;

   if (SH2TrackInfLoopInit(SSH2) != 0)
      return -1;

   SSH2->onchip.BCR1 = 0x8000;
   SSH2->isslave = 1;

   // So which core do we want?
   if (coreid == SH2CORE_DEFAULT)
      coreid = 0; // Assume we want the first one

   // Go through core list and find the id
   for (i = 0; SH2CoreList[i] != NULL; i++)
   {
      if (SH2CoreList[i]->id == coreid)
      {
         // Set to current core
         SH2Core = SH2CoreList[i];
         break;
      }
   }

   if ((SH2Core == NULL) || (SH2Core->Init() != 0)) {
      free(MSH2);
      free(SSH2);
      MSH2 = SSH2 = NULL;
      return -1;
   }

   return 0;
}