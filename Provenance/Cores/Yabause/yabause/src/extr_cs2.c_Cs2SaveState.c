#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  mpegstm_struct ;
typedef  int /*<<< orphan*/  mpegcon_struct ;
typedef  int /*<<< orphan*/  filter_struct ;
typedef  int /*<<< orphan*/  dirrec_struct ;
typedef  int /*<<< orphan*/  blockregs_struct ;
typedef  int /*<<< orphan*/  block_struct ;
struct TYPE_7__ {int _periodictiming; scalar_t__ mpegstm; scalar_t__ mpegcon; int /*<<< orphan*/  mpegintmask; int /*<<< orphan*/  vcounter; int /*<<< orphan*/  mpegvideostatus; int /*<<< orphan*/  mpegaudiostatus; int /*<<< orphan*/  pictureinfo; int /*<<< orphan*/  actionstatus; scalar_t__ fileinfo; scalar_t__ filter; TYPE_1__* partition; scalar_t__ block; int /*<<< orphan*/  curdirsect; int /*<<< orphan*/  blockfreespace; int /*<<< orphan*/  datasectstotrans; int /*<<< orphan*/  datatranssectpos; int /*<<< orphan*/  datanumsecttrans; int /*<<< orphan*/  datatransoffset; int /*<<< orphan*/  datatranspartitionnum; int /*<<< orphan*/  outconhostnum; int /*<<< orphan*/  outconmpegromnum; int /*<<< orphan*/  outconmpegbufnum; int /*<<< orphan*/  outconmpegfbnum; int /*<<< orphan*/  outconcddevnum; int /*<<< orphan*/  _commandtiming; int /*<<< orphan*/  _command; int /*<<< orphan*/  lastbuffer; int /*<<< orphan*/  transfileinfo; int /*<<< orphan*/  isaudio; int /*<<< orphan*/  speed1x; int /*<<< orphan*/  isbufferfull; int /*<<< orphan*/  isdiskchanged; int /*<<< orphan*/  isonesectorstored; int /*<<< orphan*/  datatranstype; int /*<<< orphan*/  infotranstype; int /*<<< orphan*/  calcsize; int /*<<< orphan*/  putsectsize; int /*<<< orphan*/  getsectsize; int /*<<< orphan*/  playendFAD; int /*<<< orphan*/  playFAD; scalar_t__ TOC; int /*<<< orphan*/  cdwnum; int /*<<< orphan*/  transfercount; int /*<<< orphan*/  mpgauth; int /*<<< orphan*/  satauth; int /*<<< orphan*/  index; int /*<<< orphan*/  track; int /*<<< orphan*/  ctrladdr; int /*<<< orphan*/  repcnt; int /*<<< orphan*/  options; int /*<<< orphan*/  status; int /*<<< orphan*/  FAD; int /*<<< orphan*/  reg; int /*<<< orphan*/  carttype; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  numblocks; scalar_t__ blocknum; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_4__* Cs2Area ; 
 int MAX_BLOCKS ; 
 int MAX_FILES ; 
 int MAX_SELECTORS ; 
 int StateFinishHeader (int /*<<< orphan*/ *,int) ; 
 int StateWriteHeader (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ywrite (TYPE_2__*,void*,int,int,int /*<<< orphan*/ *) ; 

int Cs2SaveState(FILE * fp) {
   int offset, i;
   IOCheck_struct check = { 0, 0 };

   // This is mostly kludge, but it will have to do until I have time to rewrite it all

   offset = StateWriteHeader(fp, "CS2 ", 2);

   // Write cart type
   ywrite(&check, (void *) &Cs2Area->carttype, 4, 1, fp);

   // Write cd block registers
   ywrite(&check, (void *) &Cs2Area->reg, sizeof(blockregs_struct), 1, fp);

   // Write current Status variables(needs a rewrite)
   ywrite(&check, (void *) &Cs2Area->FAD, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->status, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->options, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->repcnt, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->ctrladdr, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->track, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->index, 1, 1, fp);

   // Write other cd block internal variables
   ywrite(&check, (void *) &Cs2Area->satauth, 2, 1, fp);
   ywrite(&check, (void *) &Cs2Area->mpgauth, 2, 1, fp);
   ywrite(&check, (void *) &Cs2Area->transfercount, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->cdwnum, 4, 1, fp);
   ywrite(&check, (void *) Cs2Area->TOC, 4, 102, fp);
   ywrite(&check, (void *) &Cs2Area->playFAD, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->playendFAD, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->getsectsize, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->putsectsize, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->calcsize, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->infotranstype, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->datatranstype, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->isonesectorstored, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->isdiskchanged, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->isbufferfull, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->speed1x, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->isaudio, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->transfileinfo, 1, 12, fp);
   ywrite(&check, (void *) &Cs2Area->lastbuffer, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->_command, 1, 1, fp);
   {
      u32 temp = (Cs2Area->_periodictiming + 3) / 3;
      ywrite(&check, (void *) &temp, 4, 1, fp);
   }
   ywrite(&check, (void *) &Cs2Area->_commandtiming, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->outconcddevnum, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->outconmpegfbnum, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->outconmpegbufnum, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->outconmpegromnum, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->outconhostnum, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->datatranspartitionnum, 1, 1, fp);
   ywrite(&check, (void *) &Cs2Area->datatransoffset, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->datanumsecttrans, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->datatranssectpos, 2, 1, fp);
   ywrite(&check, (void *) &Cs2Area->datasectstotrans, 2, 1, fp);
   ywrite(&check, (void *) &Cs2Area->blockfreespace, 4, 1, fp);
   ywrite(&check, (void *) &Cs2Area->curdirsect, 4, 1, fp);

   // Write CD buffer
   ywrite(&check, (void *)Cs2Area->block, sizeof(block_struct), MAX_BLOCKS, fp);

   // Write partition data
   for (i = 0; i < MAX_SELECTORS; i++)
   {
      ywrite(&check, (void *)&Cs2Area->partition[i].size, 4, 1, fp);
      ywrite(&check, (void *)Cs2Area->partition[i].blocknum, 1, MAX_BLOCKS, fp);
      ywrite(&check, (void *)&Cs2Area->partition[i].numblocks, 1, 1, fp);
   }

   // Write filter data
   ywrite(&check, (void *)Cs2Area->filter, sizeof(filter_struct), MAX_SELECTORS, fp);

   // Write File Info Table
   ywrite(&check, (void *)Cs2Area->fileinfo, sizeof(dirrec_struct), MAX_FILES, fp);

   // Write MPEG card registers here

   // Write current MPEG card status variables
   ywrite(&check, (void *)&Cs2Area->actionstatus, 1, 1, fp);
   ywrite(&check, (void *)&Cs2Area->pictureinfo, 1, 1, fp);
   ywrite(&check, (void *)&Cs2Area->mpegaudiostatus, 1, 1, fp);
   ywrite(&check, (void *)&Cs2Area->mpegvideostatus, 2, 1, fp);
   ywrite(&check, (void *)&Cs2Area->vcounter, 2, 1, fp);

   // Write other MPEG card internal variables
   ywrite(&check, (void *)&Cs2Area->mpegintmask, 4, 1, fp);
   ywrite(&check, (void *)Cs2Area->mpegcon, sizeof(mpegcon_struct), 2, fp);
   ywrite(&check, (void *)Cs2Area->mpegstm, sizeof(mpegstm_struct), 2, fp);

   return StateFinishHeader(fp, offset);
}