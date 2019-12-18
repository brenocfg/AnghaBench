#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {int CR1; int CR2; int CR3; int CR4; int /*<<< orphan*/  HIRQ; } ;
struct TYPE_6__ {int playFAD; int FAD; int maxrepeat; int playendFAD; TYPE_2__ reg; int /*<<< orphan*/  status; TYPE_1__* cdi; int /*<<< orphan*/  playtype; void* index; void* track; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ReadAheadFAD ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDB_HIRQ_CMOK ; 
 int /*<<< orphan*/  CDB_PLAYTYPE_SECTOR ; 
 int /*<<< orphan*/  CDB_STAT_PLAY ; 
 int /*<<< orphan*/  CDLOG (char*,int) ; 
 TYPE_3__* Cs2Area ; 
 void* Cs2FADToTrack (int) ; 
 int /*<<< orphan*/  Cs2SetTiming (int) ; 
 int /*<<< orphan*/  Cs2SetupDefaultPlayStats (void*,int) ; 
 void* Cs2TrackToFAD (int) ; 
 int /*<<< orphan*/  doCDReport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int) ; 

void Cs2PlayDisc(void) {
  u32 pdspos;
  u32 pdepos;
  u32 pdpmode;

  // Get all the arguments
  pdspos = ((Cs2Area->reg.CR1 & 0xFF) << 16) | Cs2Area->reg.CR2;
  pdepos = ((Cs2Area->reg.CR3 & 0xFF) << 16) | Cs2Area->reg.CR4;
  pdpmode = Cs2Area->reg.CR3 >> 8;

  // Convert Start Position to playFAD
  if (pdspos == 0xFFFFFF || pdpmode == 0xFF) // This still isn't right
  {
     // No Change
  }
  else if (pdspos & 0x800000)
  {
     // FAD Mode
     Cs2Area->playFAD = (pdspos & 0xFFFFF);

     Cs2SetupDefaultPlayStats(Cs2FADToTrack(Cs2Area->playFAD), 0);

     if (!(pdpmode & 0x80))
        // Move pickup to start position
        Cs2Area->FAD = Cs2Area->playFAD;
  }
  else
  {
     // Track Mode

     // If track == 0, set it to the first available track, or something like that
     if (pdspos == 0)
        pdspos = 0x0100;

     if (!(pdpmode & 0x80))
     {
        Cs2SetupDefaultPlayStats((u8)(pdspos >> 8), 1);
        Cs2Area->playFAD = Cs2Area->FAD;
        Cs2Area->track = (u8)(pdspos >> 8);
        Cs2Area->index = (u8)pdspos;
     }
     else
     {
        // Preserve Pickup Position
        Cs2SetupDefaultPlayStats((u8)(pdspos >> 8), 0);
     }
  }

  pdpmode &= 0x7F;

  // Only update max repeat if bits 0-6 aren't all set
  if (pdpmode != 0x7F)
     Cs2Area->maxrepeat = pdpmode;

  // Convert End Position to playendFAD
  if (pdepos == 0xFFFFFF)
  {
     // No Change
  }
  else if (pdepos & 0x800000)
  {
     // FAD Mode
     Cs2Area->playendFAD = Cs2Area->playFAD+(pdepos & 0xFFFFF);
  }
  else if (pdepos != 0)
  {
     // To the next track (Fixes "no music" in games like Sega Rally)
     pdepos += 0x100;
     // Track Mode
     if ((pdepos & 0xFF) == 0)
        Cs2Area->playendFAD = Cs2TrackToFAD((u16)(pdepos | 0x0063));
     else
        Cs2Area->playendFAD = Cs2TrackToFAD((u16)pdepos);
  }
  else
  {
     // Default Mode
     Cs2Area->playendFAD = Cs2TrackToFAD(0xFFFF);
  }

  // setup play mode here
#if CDDEBUG
  if (pdpmode != 0)
     CDLOG("cs2\t: playDisc: Unsupported play mode = %02X\n", pdpmode);
#endif

  Cs2SetTiming(1);

  Cs2Area->status = CDB_STAT_PLAY;
  Cs2Area->playtype = CDB_PLAYTYPE_SECTOR;
  Cs2Area->cdi->ReadAheadFAD(Cs2Area->FAD);

  doCDReport(Cs2Area->status);
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK;
}