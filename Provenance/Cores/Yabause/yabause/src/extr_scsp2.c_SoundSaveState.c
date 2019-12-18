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
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_9__ {int (* GetDReg ) (int) ;int (* GetAReg ) (int) ;int (* GetSR ) () ;int (* GetPC ) () ;} ;
struct TYPE_8__ {int mem4mb; int mvol; int rbl; int mslc; int drga; int dgate; int ddir; int dexe; int dtlg; int mofull; int moemp; int miovf; int mifull; int miemp; int tima; int tactl; int timb; int tbctl; int timc; int tcctl; int scieb; int scipd; int scilv0; int scilv1; int scilv2; int mcieb; int mcipd; scalar_t__ stack; int /*<<< orphan*/  midi_out_cnt; int /*<<< orphan*/  midi_in_cnt; scalar_t__ midi_out_buf; scalar_t__ midi_in_buf; int /*<<< orphan*/  dmea; int /*<<< orphan*/  rbp; TYPE_1__* slot; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {scalar_t__ env_phase; int /*<<< orphan*/  lfo_step; int /*<<< orphan*/  lfo_counter; int /*<<< orphan*/  env_target; int /*<<< orphan*/  env_step; int /*<<< orphan*/  env_counter; int /*<<< orphan*/  addr_counter; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_5__* M68K ; 
 scalar_t__ SCSP_ENV_ATTACK ; 
 scalar_t__ SCSP_ENV_DECAY ; 
 scalar_t__ SCSP_ENV_RELEASE ; 
 scalar_t__ SCSP_ENV_SUSTAIN ; 
 int /*<<< orphan*/  ScspSyncThread () ; 
 scalar_t__ SoundRam ; 
 int StateFinishHeader (int /*<<< orphan*/ *,int) ; 
 int StateWriteHeader (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  m68k_running ; 
 TYPE_4__ scsp ; 
 scalar_t__ scsp_regcache ; 
 scalar_t__ scsp_thread_running ; 
 int stub1 (int) ; 
 int stub2 (int) ; 
 int stub3 () ; 
 int stub4 () ; 
 int /*<<< orphan*/  ywrite (TYPE_2__*,void*,int,int,int /*<<< orphan*/ *) ; 

int SoundSaveState(FILE *fp)
{
   int i;
   u32 temp;
   u8 temp8;
   int offset;
   IOCheck_struct check = { 0, 0 };

   if (scsp_thread_running)
      ScspSyncThread();

   offset = StateWriteHeader(fp, "SCSP", 2);

   // Save 68k registers first
   ywrite(&check, (void *)&m68k_running, 1, 1, fp);
   for (i = 0; i < 8; i++)
   {
      temp = M68K->GetDReg(i);
      ywrite(&check, (void *)&temp, 4, 1, fp);
   }
   for (i = 0; i < 8; i++)
   {
      temp = M68K->GetAReg(i);
      ywrite(&check, (void *)&temp, 4, 1, fp);
   }
   temp = M68K->GetSR();
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = M68K->GetPC();
   ywrite(&check, (void *)&temp, 4, 1, fp);

   // Now for the SCSP registers
   ywrite(&check, (void *)scsp_regcache, 0x1000, 1, fp);

   // Sound RAM is important
   ywrite(&check, (void *)SoundRam, 0x80000, 1, fp);

   // Write slot internal variables
   for (i = 0; i < 32; i++)
   {
      ywrite(&check, (void *)&scsp.slot[i].key, 1, 1, fp);
      ywrite(&check, (void *)&scsp.slot[i].addr_counter, 4, 1, fp);
      ywrite(&check, (void *)&scsp.slot[i].env_counter, 4, 1, fp);
      ywrite(&check, (void *)&scsp.slot[i].env_step, 4, 1, fp);
      ywrite(&check, (void *)&scsp.slot[i].env_target, 4, 1, fp);
      ywrite(&check, (void *)&scsp.slot[i].env_phase, 4, 1, fp);

      // Was enxt in scsp1; we don't use it, so just derive the proper
      // value from env_phase
      if (scsp.slot[i].env_phase == SCSP_ENV_RELEASE)
         temp8 = 1;
      else if (scsp.slot[i].env_phase == SCSP_ENV_SUSTAIN)
         temp8 = 2;
      else if (scsp.slot[i].env_phase == SCSP_ENV_DECAY)
         temp8 = 3;
      else if (scsp.slot[i].env_phase == SCSP_ENV_ATTACK)
         temp8 = 4;
      else  // impossible, but avoid "undefined value" warnings
         temp8 = 0;
      ywrite(&check, (void *)&temp8, 1, 1, fp);

      ywrite(&check, (void *)&scsp.slot[i].lfo_counter, 4, 1, fp);
      ywrite(&check, (void *)&scsp.slot[i].lfo_step, 4, 1, fp);
   }

   // Write main internal variables
   // FIXME/SCSP1: need to write a lot of these from temporary variables
   // to maintain save state compatibility
   temp = scsp.mem4mb;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.mvol;
   ywrite(&check, (void *)&temp, 4, 1, fp);

   temp = scsp.rbl;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   ywrite(&check, (void *)&scsp.rbp, 4, 1, fp);

   temp = scsp.mslc;
   ywrite(&check, (void *)&temp, 4, 1, fp);

   ywrite(&check, (void *)&scsp.dmea, 4, 1, fp);
   temp = scsp.drga;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.dgate<<6 | scsp.ddir<<5 | scsp.dexe<<4;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.dtlg;
   ywrite(&check, (void *)&temp, 4, 1, fp);

   ywrite(&check, (void *)scsp.midi_in_buf, 1, 4, fp);
   ywrite(&check, (void *)scsp.midi_out_buf, 1, 4, fp);
   ywrite(&check, (void *)&scsp.midi_in_cnt, 1, 1, fp);
   ywrite(&check, (void *)&scsp.midi_out_cnt, 1, 1, fp);
   temp8 = scsp.mofull<<4 | scsp.moemp<<3
         | scsp.miovf<<2 | scsp.mifull<<1 | scsp.miemp<<0;
   ywrite(&check, (void *)&temp8, 1, 1, fp);

   temp = scsp.tima;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.tactl;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.timb;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.tbctl;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.timc;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.tcctl;
   ywrite(&check, (void *)&temp, 4, 1, fp);

   temp = scsp.scieb;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.scipd;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.scilv0;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.scilv1;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.scilv2;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.mcieb;
   ywrite(&check, (void *)&temp, 4, 1, fp);
   temp = scsp.mcipd;
   ywrite(&check, (void *)&temp, 4, 1, fp);

   ywrite(&check, (void *)scsp.stack, 4, 32 * 2, fp);

   return StateFinishHeader(fp, offset);
}