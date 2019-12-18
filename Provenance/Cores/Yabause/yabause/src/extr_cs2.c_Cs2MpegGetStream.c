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
struct TYPE_5__ {int CR3; int CR1; int CR2; int CR4; int HIRQ; } ;
struct TYPE_6__ {int status; TYPE_2__ reg; TYPE_1__* mpegstm; } ;
struct TYPE_4__ {int audstm; int audstmid; int audchannum; int vidstm; int vidstmid; int vidchannum; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_MPCM ; 
 TYPE_3__* Cs2Area ; 

void Cs2MpegGetStream(void) {
   int mgsnext = (Cs2Area->reg.CR3 >> 8);

   if (mgsnext == 0)
   {
      // Current
      Cs2Area->reg.CR1 = (Cs2Area->status << 8) | Cs2Area->mpegstm[0].audstm;
      Cs2Area->reg.CR2 = (Cs2Area->mpegstm[0].audstmid << 8) | Cs2Area->mpegstm[0].audchannum;
      Cs2Area->reg.CR3 = Cs2Area->mpegstm[0].vidstm;
      Cs2Area->reg.CR4 = (Cs2Area->mpegstm[0].vidstmid << 8) | Cs2Area->mpegstm[0].vidchannum;
   }
   else
   {
      // Next
      Cs2Area->reg.CR1 = (Cs2Area->status << 8) | Cs2Area->mpegstm[1].audstm;
      Cs2Area->reg.CR2 = (Cs2Area->mpegstm[1].audstmid << 8) | Cs2Area->mpegstm[1].audchannum;
      Cs2Area->reg.CR3 = Cs2Area->mpegstm[1].vidstm;
      Cs2Area->reg.CR4 = (Cs2Area->mpegstm[1].vidstmid << 8) | Cs2Area->mpegstm[1].vidchannum;
   }

   Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_MPCM;
}