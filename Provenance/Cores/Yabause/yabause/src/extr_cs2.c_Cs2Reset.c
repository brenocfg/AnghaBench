#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_9__ {int CR1; char CR2; char CR3; char CR4; int HIRQ; int HIRQMASK; } ;
struct TYPE_16__ {int FAD; int options; int repcnt; int ctrladdr; int track; int index; int infotranstype; int datatranstype; int getsectsize; int putsectsize; int isdiskchanged; int playFAD; int playendFAD; int blockfreespace; int lastbuffer; int _statustiming; TYPE_6__* mpegstm; TYPE_5__* mpegcon; scalar_t__ _commandtiming; scalar_t__ _periodiccycles; scalar_t__ _statuscycles; scalar_t__ _command; scalar_t__ numfiles; int /*<<< orphan*/  fileinfo; scalar_t__ curdirfidoffset; scalar_t__ curdirsize; scalar_t__ curdirsect; int /*<<< orphan*/ * TOC; TYPE_4__* block; TYPE_3__* partition; TYPE_2__* filter; scalar_t__ mpgauth; scalar_t__ satauth; scalar_t__ maxrepeat; scalar_t__ playtype; TYPE_1__ reg; scalar_t__ isaudio; scalar_t__ isonesectorstored; scalar_t__ isbufferfull; scalar_t__ cdwnum; scalar_t__ transfercount; int /*<<< orphan*/  status; TYPE_7__* cdi; } ;
struct TYPE_15__ {int (* GetStatus ) () ;} ;
struct TYPE_14__ {int audstm; int vidstm; int audstmid; int vidstmid; int audchannum; int vidchannum; } ;
struct TYPE_13__ {int audcon; int vidcon; int audlay; int vidlay; int audbufnum; int vidbufnum; } ;
struct TYPE_12__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {int size; int* blocknum; int /*<<< orphan*/ ** block; scalar_t__ numblocks; } ;
struct TYPE_10__ {int range; int condfalse; scalar_t__ condtrue; scalar_t__ cival; scalar_t__ smval; scalar_t__ fid; scalar_t__ cimask; scalar_t__ smmask; scalar_t__ chan; scalar_t__ mode; scalar_t__ FAD; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDB_STAT_NODISC ; 
 int /*<<< orphan*/  CDB_STAT_OPEN ; 
 int /*<<< orphan*/  CDB_STAT_PAUSE ; 
 TYPE_8__* Cs2Area ; 
 int /*<<< orphan*/  Cs2SetTiming (int /*<<< orphan*/ ) ; 
 size_t MAX_BLOCKS ; 
 size_t MAX_SELECTORS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int stub1 () ; 

void Cs2Reset(void) {
  u32 i, i2;

  switch (Cs2Area->cdi->GetStatus())
  {
     case 0:
     case 1:
             Cs2Area->status = CDB_STAT_PAUSE;
             Cs2Area->FAD = 150;
             Cs2Area->options = 0;
             Cs2Area->repcnt = 0;
             Cs2Area->ctrladdr = 0x41;
             Cs2Area->track = 1;
             Cs2Area->index = 1;
             break;
     case 2:
             Cs2Area->status = CDB_STAT_NODISC;

             Cs2Area->FAD = 0xFFFFFFFF;
             Cs2Area->options = 0xFF;
             Cs2Area->repcnt = 0xFF;
             Cs2Area->ctrladdr = 0xFF;
             Cs2Area->track = 0xFF;
             Cs2Area->index = 0xFF;
             break;
     case 3:
             Cs2Area->status = CDB_STAT_OPEN;

             Cs2Area->FAD = 0xFFFFFFFF;
             Cs2Area->options = 0xFF;
             Cs2Area->repcnt = 0xFF;
             Cs2Area->ctrladdr = 0xFF;
             Cs2Area->track = 0xFF;
             Cs2Area->index = 0xFF;
             break;
     default: break;
  }

  Cs2Area->infotranstype = -1;
  Cs2Area->datatranstype = -1;
  Cs2Area->transfercount = 0;
  Cs2Area->cdwnum = 0;
  Cs2Area->getsectsize = Cs2Area->putsectsize = 2048;
  Cs2Area->isdiskchanged = 1;
  Cs2Area->isbufferfull = 0;
  Cs2Area->isonesectorstored = 0;
  Cs2Area->isaudio = 0;

  Cs2Area->reg.CR1 = ( 0 <<8) | 'C';
  Cs2Area->reg.CR2 = ('D'<<8) | 'B';
  Cs2Area->reg.CR3 = ('L'<<8) | 'O';
  Cs2Area->reg.CR4 = ('C'<<8) | 'K';
  Cs2Area->reg.HIRQ = 0xFFFF;
  Cs2Area->reg.HIRQMASK = 0xFFFF;

  Cs2Area->playFAD = 0xFFFFFFFF;
  Cs2Area->playendFAD = 0xFFFFFFFF;
  Cs2Area->playtype = 0;
  Cs2Area->maxrepeat = 0;

  // set authentication variables to 0(not authenticated)
  Cs2Area->satauth = 0;
  Cs2Area->mpgauth = 0;

  // clear filter conditions
  for (i = 0; i < MAX_SELECTORS; i++)
  {
     Cs2Area->filter[i].FAD = 0;
     Cs2Area->filter[i].range = 0xFFFFFFFF;
     Cs2Area->filter[i].mode = 0;
     Cs2Area->filter[i].chan = 0;
     Cs2Area->filter[i].smmask = 0;
     Cs2Area->filter[i].cimask = 0;
     Cs2Area->filter[i].fid = 0;
     Cs2Area->filter[i].smval = 0;
     Cs2Area->filter[i].cival = 0;
     Cs2Area->filter[i].condtrue = 0;
     Cs2Area->filter[i].condfalse = 0xFF;
  }

  // clear partitions
  for (i = 0; i < MAX_SELECTORS; i++)
  {
     Cs2Area->partition[i].size = -1;
     Cs2Area->partition[i].numblocks = 0;

     for (i2 = 0; i2 < MAX_BLOCKS; i2++)
     {
        Cs2Area->partition[i].block[i2] = NULL;
        Cs2Area->partition[i].blocknum[i2] = 0xFF;
     }
  }

  // clear blocks
  for (i = 0; i < MAX_BLOCKS; i++)
  {
     Cs2Area->block[i].size = -1;
     memset(Cs2Area->block[i].data, 0, 2352);
  }

  Cs2Area->blockfreespace = 200;

  // initialize TOC
  memset(Cs2Area->TOC, 0xFF, sizeof(Cs2Area->TOC));

  // clear filesystem stuff
  Cs2Area->curdirsect = 0;
  Cs2Area->curdirsize = 0;
  Cs2Area->curdirfidoffset = 0;
  memset(&Cs2Area->fileinfo, 0, sizeof(Cs2Area->fileinfo));
  Cs2Area->numfiles = 0;

  Cs2Area->lastbuffer = 0xFF;

  Cs2Area->_command = 0;
  Cs2Area->_statuscycles = 0;
  Cs2Area->_statustiming = 1000000;
  Cs2Area->_periodiccycles = 0;
  Cs2Area->_commandtiming = 0;
  Cs2SetTiming(0);

  // MPEG specific stuff
  Cs2Area->mpegcon[0].audcon = Cs2Area->mpegcon[0].vidcon = 0x00;
  Cs2Area->mpegcon[0].audlay = Cs2Area->mpegcon[0].vidlay = 0x00;
  Cs2Area->mpegcon[0].audbufnum = Cs2Area->mpegcon[0].vidbufnum = 0xFF;
  Cs2Area->mpegcon[1].audcon = Cs2Area->mpegcon[1].vidcon = 0x00;
  Cs2Area->mpegcon[1].audlay = Cs2Area->mpegcon[1].vidlay = 0x00;
  Cs2Area->mpegcon[1].audbufnum = Cs2Area->mpegcon[1].vidbufnum = 0xFF;

  // should verify the following
  Cs2Area->mpegstm[0].audstm = Cs2Area->mpegstm[0].vidstm = 0x00;
  Cs2Area->mpegstm[0].audstmid = Cs2Area->mpegstm[0].vidstmid = 0x00;
  Cs2Area->mpegstm[0].audchannum = Cs2Area->mpegstm[0].vidchannum = 0x00;
  Cs2Area->mpegstm[1].audstm = Cs2Area->mpegstm[1].vidstm = 0x00;
  Cs2Area->mpegstm[1].audstmid = Cs2Area->mpegstm[1].vidstmid = 0x00;
  Cs2Area->mpegstm[1].audchannum = Cs2Area->mpegstm[1].vidchannum = 0x00;
}