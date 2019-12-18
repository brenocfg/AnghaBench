#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_9__ {size_t numblocks; scalar_t__ size; TYPE_7__** block; int /*<<< orphan*/ * blocknum; } ;
typedef  TYPE_2__ partition_struct ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_8__ {int CR1; int CR2; scalar_t__ CR4; int HIRQ; } ;
struct TYPE_11__ {int mpgauth; int getsectsize; int isonesectorstored; TYPE_1__ reg; int /*<<< orphan*/  status; int /*<<< orphan*/  isbufferfull; scalar_t__ outconmpegrom; scalar_t__ mpegpath; scalar_t__ outconmpegromnum; scalar_t__ filter; } ;
struct TYPE_10__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_CSCT ; 
 int CDB_HIRQ_MPED ; 
 TYPE_7__* Cs2AllocateBlock (int /*<<< orphan*/ *) ; 
 TYPE_6__* Cs2Area ; 
 TYPE_2__* Cs2GetPartition (scalar_t__) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  doCDReport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (scalar_t__,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yread (TYPE_3__*,void*,int,int,int /*<<< orphan*/ *) ; 

void Cs2GetMPEGRom(void) {
  u16 i;
  FILE * mpgfp;
  partition_struct * mpgpartition;

  // fix me
  Cs2Area->mpgauth |= 0x300;

  Cs2Area->outconmpegrom = Cs2Area->filter + 0;
  Cs2Area->outconmpegromnum = 0;

  if (Cs2Area->mpegpath && (mpgfp = fopen(Cs2Area->mpegpath, "rb")) != NULL)
  {
     u32 readoffset = ((Cs2Area->reg.CR1 & 0xFF) << 8) | Cs2Area->reg.CR2;
     u16 readsize = Cs2Area->reg.CR4;

     fseek(mpgfp, readoffset * Cs2Area->getsectsize, SEEK_SET);
     if ((mpgpartition = Cs2GetPartition(Cs2Area->outconmpegrom)) != NULL && !Cs2Area->isbufferfull)
     {
        IOCheck_struct check = { 0, 0 };
        mpgpartition->size = 0;

        for (i = 0; i < readsize; i++)
        {
           mpgpartition->block[mpgpartition->numblocks] = Cs2AllocateBlock(&mpgpartition->blocknum[mpgpartition->numblocks]);

           if (mpgpartition->block[mpgpartition->numblocks] != NULL) {
              // read data
              yread(&check, (void *)mpgpartition->block[mpgpartition->numblocks]->data, 1, Cs2Area->getsectsize, mpgfp);

              mpgpartition->numblocks++;
              mpgpartition->size += Cs2Area->getsectsize;
           }
        }

        Cs2Area->isonesectorstored = 1;
        Cs2Area->reg.HIRQ |= CDB_HIRQ_CSCT;
     }

     fclose(mpgfp);
  }

  doCDReport(Cs2Area->status);
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_MPED;
}