#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_7__ {int CR1; int CR2; int CR3; int CR4; int /*<<< orphan*/  HIRQ; } ;
struct TYPE_8__ {int getsectsize; int options; TYPE_3__ reg; int /*<<< orphan*/  status; scalar_t__ FAD; TYPE_2__* cdi; int /*<<< orphan*/  playtype; scalar_t__ filter; scalar_t__ outconcddev; scalar_t__ playFAD; scalar_t__ playendFAD; TYPE_1__* fileinfo; scalar_t__ maxrepeat; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ReadAheadFAD ) (scalar_t__) ;} ;
struct TYPE_5__ {int size; scalar_t__ lba; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDB_HIRQ_CMOK ; 
 int /*<<< orphan*/  CDB_PLAYTYPE_FILE ; 
 int /*<<< orphan*/  CDB_STAT_PLAY ; 
 TYPE_4__* Cs2Area ; 
 int /*<<< orphan*/  Cs2FADToTrack (scalar_t__) ; 
 int /*<<< orphan*/  Cs2SetTiming (int) ; 
 int /*<<< orphan*/  Cs2SetupDefaultPlayStats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doCDReport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void Cs2ReadFile(void) {
  u32 rfoffset, rffilternum, rffid, rfsize;

  rfoffset = ((Cs2Area->reg.CR1 & 0xFF) << 8) | Cs2Area->reg.CR2;
  rffilternum = Cs2Area->reg.CR3 >> 8;
  rffid = ((Cs2Area->reg.CR3 & 0xFF) << 8) | Cs2Area->reg.CR4;
  rfsize = ((Cs2Area->fileinfo[rffid].size + Cs2Area->getsectsize - 1) /
           Cs2Area->getsectsize) - rfoffset;

  Cs2SetupDefaultPlayStats(Cs2FADToTrack(Cs2Area->fileinfo[rffid].lba + rfoffset), 0);
  Cs2Area->maxrepeat = 0;

  Cs2Area->playFAD = Cs2Area->FAD = Cs2Area->fileinfo[rffid].lba + rfoffset;
  Cs2Area->playendFAD = Cs2Area->playFAD + rfsize;

  Cs2Area->options = 0x8;

  Cs2SetTiming(1);

  Cs2Area->outconcddev = Cs2Area->filter + rffilternum;

  Cs2Area->status = CDB_STAT_PLAY;
  Cs2Area->playtype = CDB_PLAYTYPE_FILE;
  Cs2Area->cdi->ReadAheadFAD(Cs2Area->FAD);

  doCDReport(Cs2Area->status);
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK;
}