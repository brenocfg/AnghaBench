#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  numblocks; } ;
typedef  TYPE_3__ partition_struct ;
struct TYPE_7__ {int /*<<< orphan*/  HIRQ; } ;
struct TYPE_9__ {scalar_t__ _statuscycles; scalar_t__ _periodiccycles; int _commandtiming; scalar_t__ _statustiming; int status; int isdiskchanged; scalar_t__ _periodictiming; int isonesectorstored; int repcnt; int maxrepeat; scalar_t__ carttype; TYPE_2__ reg; scalar_t__ _command; int /*<<< orphan*/  FAD; void* track; int /*<<< orphan*/  playFAD; int /*<<< orphan*/  playtype; int /*<<< orphan*/  playendFAD; int /*<<< orphan*/  isbufferfull; int /*<<< orphan*/  blockfreespace; int /*<<< orphan*/  partition; TYPE_1__* cdi; } ;
struct TYPE_6__ {int (* GetStatus ) () ;int /*<<< orphan*/  (* ReadAheadFAD ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CART_JAPMODEM ; 
 scalar_t__ CART_NETLINK ; 
 int /*<<< orphan*/  CDB_HIRQ_CSCT ; 
 int /*<<< orphan*/  CDB_HIRQ_EFLS ; 
 int /*<<< orphan*/  CDB_HIRQ_PEND ; 
 int /*<<< orphan*/  CDB_HIRQ_SCDQ ; 
 int /*<<< orphan*/  CDB_PLAYTYPE_FILE ; 
 int CDB_STAT_NODISC ; 
 int CDB_STAT_OPEN ; 
#define  CDB_STAT_PAUSE 132 
 int CDB_STAT_PERI ; 
#define  CDB_STAT_PLAY 131 
#define  CDB_STAT_RETRY 130 
#define  CDB_STAT_SCAN 129 
#define  CDB_STAT_SEEK 128 
 int /*<<< orphan*/  CDLOG (char*,...) ; 
 TYPE_5__* Cs2Area ; 
 int /*<<< orphan*/  Cs2Execute () ; 
 void* Cs2FADToTrack (int /*<<< orphan*/ ) ; 
 int Cs2ReadFilteredSector (int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  Cs2SetTiming (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JapModemExec (int) ; 
 int /*<<< orphan*/  NetlinkExec (int) ; 
 int /*<<< orphan*/  doCDReport (int) ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void Cs2Exec(u32 timing) {
   Cs2Area->_statuscycles += timing * 3;
   Cs2Area->_periodiccycles += timing * 3;

   if (Cs2Area->_commandtiming > 0)
   {
      if (Cs2Area->_commandtiming < timing)
      {
         Cs2Execute();
         Cs2Area->_commandtiming = 0;
      }
      else
         Cs2Area->_commandtiming -= timing;
   }

   if (Cs2Area->_statuscycles >= Cs2Area->_statustiming)
   {
      Cs2Area->_statuscycles -= Cs2Area->_statustiming;
      switch(Cs2Area->cdi->GetStatus())
      {
         case 0:
         case 1:
            if ((Cs2Area->status & 0xF) == CDB_STAT_NODISC ||
                (Cs2Area->status & 0xF) == CDB_STAT_OPEN)
            {
               Cs2Area->status = CDB_STAT_PAUSE;
               Cs2Area->isdiskchanged = 1;
            }
            break;
         case 2:
            // may need to change this
            if ((Cs2Area->status & 0xF) != CDB_STAT_NODISC)
               Cs2Area->status = CDB_STAT_NODISC;
            break;
         case 3:
            // may need to change this
            if ((Cs2Area->status & 0xF) != CDB_STAT_OPEN)
               Cs2Area->status = CDB_STAT_OPEN;
            break;
         default: break;
      }
   }

   if (Cs2Area->_periodiccycles >= Cs2Area->_periodictiming)
   {
      Cs2Area->_periodiccycles -= Cs2Area->_periodictiming;

      // Get Drive's current status and compare with old status
      switch (Cs2Area->status & 0xF) {
         case CDB_STAT_PAUSE:
         {
//            if (FAD >= playFAD && FAD < playendFAD)
//               status = CDB_STAT_PLAY;
//            else
               break;
         }
         case CDB_STAT_PLAY:
         {
            partition_struct * playpartition;
            int ret = Cs2ReadFilteredSector(Cs2Area->FAD, &playpartition);

            switch (ret)
            {
               case 0:
                  // Sector Read OK
                  Cs2Area->FAD++;
                  Cs2Area->cdi->ReadAheadFAD(Cs2Area->FAD);

                  if (playpartition != NULL)
                  {
                     // We can use this sector
                     CDLOG("partition number = %d blocks = %d blockfreespace = %d fad = %x playpartition->size = %x isbufferfull = %x\n", (playpartition - Cs2Area->partition), playpartition->numblocks, Cs2Area->blockfreespace, Cs2Area->FAD, playpartition->size, Cs2Area->isbufferfull);

                     Cs2Area->reg.HIRQ |= CDB_HIRQ_CSCT;
                     Cs2Area->isonesectorstored = 1;

                     if (Cs2Area->FAD >= Cs2Area->playendFAD) {
                        // Make sure we don't have to do a repeat
                        if (Cs2Area->repcnt >= Cs2Area->maxrepeat) {
                           // we're done
                           Cs2Area->status = CDB_STAT_PAUSE;
                           Cs2SetTiming(0);
                           Cs2Area->reg.HIRQ |= CDB_HIRQ_PEND;

                           if (Cs2Area->playtype == CDB_PLAYTYPE_FILE)
                              Cs2Area->reg.HIRQ |= CDB_HIRQ_EFLS;

                           CDLOG("PLAY HAS ENDED\n");
                        }
                        else {

                           Cs2Area->FAD = Cs2Area->playFAD;
                           if (Cs2Area->repcnt < 0xE)
                              Cs2Area->repcnt++;
                           Cs2Area->track = Cs2FADToTrack(Cs2Area->FAD);

                           CDLOG("PLAY HAS REPEATED\n");
                        }
                     }
                     if (Cs2Area->isbufferfull) {
                        CDLOG("BUFFER IS FULL\n");
//                        status = CDB_STAT_PAUSE;
                     }
                  }
                  else
                  {
                     CDLOG("Sector filtered out\n");
                     if (Cs2Area->FAD >= Cs2Area->playendFAD) {
                        // Make sure we don't have to do a repeat
                        if (Cs2Area->repcnt >= Cs2Area->maxrepeat) {
                           // we're done
                           Cs2Area->status = CDB_STAT_PAUSE;
                           Cs2SetTiming(0);
                           Cs2Area->reg.HIRQ |= CDB_HIRQ_PEND;

                           if (Cs2Area->playtype == CDB_PLAYTYPE_FILE)
                              Cs2Area->reg.HIRQ |= CDB_HIRQ_EFLS;

                           CDLOG("PLAY HAS ENDED\n");
                        }
                        else {
                           Cs2Area->FAD = Cs2Area->playFAD;
                           if (Cs2Area->repcnt < 0xE)
                              Cs2Area->repcnt++;
                           Cs2Area->track = Cs2FADToTrack(Cs2Area->FAD);

                           CDLOG("PLAY HAS REPEATED\n");
                        }
                     }
                  }
                  break;
               case -1:
                  // Things weren't setup correctly
                  break;
               case -2:
                  // Do a read retry
                  break;
            }

            break;
         }
         case CDB_STAT_SEEK:
            break;
         case CDB_STAT_SCAN:
            break;
         case CDB_STAT_RETRY:
            break;
         default: break;
      }

      if (Cs2Area->_command)
         return;

      Cs2Area->status |= CDB_STAT_PERI;

      // adjust registers appropriately here(fix me)
      doCDReport(Cs2Area->status);

      Cs2Area->reg.HIRQ |= CDB_HIRQ_SCDQ;
   }

   if(Cs2Area->carttype == CART_NETLINK)
      NetlinkExec(timing);
   else if (Cs2Area->carttype == CART_JAPMODEM)
      JapModemExec(timing);
}