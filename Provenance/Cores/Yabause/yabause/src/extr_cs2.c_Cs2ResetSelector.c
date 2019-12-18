#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct TYPE_9__ {int CR1; int CR3; int HIRQ; } ;
struct TYPE_10__ {int blockfreespace; int datatranstype; size_t datatranspartitionnum; TYPE_4__ reg; int /*<<< orphan*/  status; scalar_t__ isonesectorstored; TYPE_3__* block; TYPE_2__* partition; scalar_t__ isbufferfull; TYPE_1__* filter; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {size_t numblocks; int* blocknum; int size; int /*<<< orphan*/ ** block; } ;
struct TYPE_6__ {int condfalse; int range; scalar_t__ cival; scalar_t__ smval; scalar_t__ fid; scalar_t__ cimask; scalar_t__ smmask; scalar_t__ chan; scalar_t__ mode; scalar_t__ FAD; scalar_t__ condtrue; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_ESEL ; 
 TYPE_5__* Cs2Area ; 
 int /*<<< orphan*/  Cs2FreeBlock (int /*<<< orphan*/ *) ; 
 size_t MAX_BLOCKS ; 
 size_t MAX_SELECTORS ; 
 int /*<<< orphan*/  doCDReport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void Cs2ResetSelector(void) {
  // still needs a bit of work
  u32 i, i2;

  if ((Cs2Area->reg.CR1 & 0xFF) == 0)
  {
     // Reset specified partition buffer only
     u32 rsbufno = Cs2Area->reg.CR3 >> 8;

     // sort remaining blocks
     if (rsbufno < MAX_SELECTORS)
     {
        // clear partition
        for (i = 0; i < Cs2Area->partition[rsbufno].numblocks; i++)
        {
           Cs2FreeBlock(Cs2Area->partition[rsbufno].block[i]);
           Cs2Area->partition[rsbufno].block[i] = NULL;
           Cs2Area->partition[rsbufno].blocknum[i] = 0xFF;
        }

        Cs2Area->partition[rsbufno].size = -1;
        Cs2Area->partition[rsbufno].numblocks = 0;
     }

     if (Cs2Area->blockfreespace > 0) Cs2Area->isbufferfull = 0;
     if (Cs2Area->blockfreespace == 200)
     {
        Cs2Area->isonesectorstored = 0;
        Cs2Area->datatranstype = -1;
     }
     else if (Cs2Area->datatranspartitionnum == rsbufno)
        Cs2Area->datatranstype = -1;

     doCDReport(Cs2Area->status);
     Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_ESEL;
     return;
  }

  // parse flags and reset the specified area(fix me)
  if (Cs2Area->reg.CR1 & 0x80)
  {
     // reset false filter output connections
     for (i = 0; i < MAX_SELECTORS; i++)
        Cs2Area->filter[i].condfalse = 0xFF;
  }

  if (Cs2Area->reg.CR1 & 0x40)
  {
     // reset true filter output connections
     for (i = 0; i < MAX_SELECTORS; i++)
        Cs2Area->filter[i].condtrue = (u8)i;
  }

  if (Cs2Area->reg.CR1 & 0x10)
  {
     // reset filter conditions
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
     }
  }

  if (Cs2Area->reg.CR1 & 0x8)
  {
     // reset partition output connectors
  }

  if (Cs2Area->reg.CR1 & 0x4)
  {
     // reset partitions buffer data
     Cs2Area->isbufferfull = 0;

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

     Cs2Area->isonesectorstored = 0;
     Cs2Area->datatranstype = -1;
  }

  doCDReport(Cs2Area->status);
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_ESEL;
}