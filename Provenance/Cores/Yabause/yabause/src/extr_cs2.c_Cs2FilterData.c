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
struct TYPE_9__ {size_t numblocks; int size; TYPE_7__** block; int /*<<< orphan*/ * blocknum; } ;
typedef  TYPE_2__ partition_struct ;
struct TYPE_10__ {int mode; scalar_t__ fid; scalar_t__ chan; int smmask; int smval; int cimask; int cival; scalar_t__ FAD; scalar_t__ range; int condtrue; int condfalse; } ;
typedef  TYPE_3__ filter_struct ;
struct TYPE_12__ {int size; scalar_t__ FAD; scalar_t__ cn; scalar_t__ fn; int sm; int ci; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int* data; scalar_t__ fn; scalar_t__ cn; int sm; int ci; scalar_t__ FAD; int size; } ;
struct TYPE_11__ {int lastbuffer; TYPE_1__ workblock; TYPE_3__* filter; TYPE_2__* partition; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDLOG (char*,...) ; 
 TYPE_7__* Cs2AllocateBlock (int /*<<< orphan*/ *) ; 
 TYPE_6__* Cs2Area ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

partition_struct * Cs2FilterData(filter_struct * curfilter, int isaudio)
{
  int condresults;
  partition_struct * fltpartition = NULL;

  for (;;)
  {
     // reset result
     condresults = 1;
     // detect which type of sector we're dealing with
     // If it's not mode 2, ignore the subheader conditions
     if (Cs2Area->workblock.data[0xF] == 0x02 && !isaudio)
     {
        // Mode 2
        // go through various subheader filter conditions

        if (curfilter->mode & 0x01)
        {
           // File Number Check
           if (Cs2Area->workblock.fn != curfilter->fid)
              condresults = 0;
        }

        if (curfilter->mode & 0x02)
        {
           // Channel Number Check
           if (Cs2Area->workblock.cn != curfilter->chan)
              condresults = 0;
        }

        if (curfilter->mode & 0x04)
        {
           // Sub Mode Check
           if ((Cs2Area->workblock.sm & curfilter->smmask) != curfilter->smval)
              condresults = 0;
        }

        if (curfilter->mode & 0x08)
        {
           // Coding Information Check
           CDLOG("cs2\t: FilterData: Coding Information Check. Coding Information = %02X. Filter's Coding Information Mask = %02X, Coding Information Value = %02X\n", Cs2Area->workblock.ci, curfilter->cimask, curfilter->cival);
           if ((Cs2Area->workblock.ci & curfilter->cimask) != curfilter->cival)
              condresults = 0;
        }

        if (curfilter->mode & 0x10)
        {
           // Reverse Subheader Conditions
           CDLOG("cs2\t: FilterData: Reverse Subheader Conditions\n");
           condresults ^= 1;
        }
     }

     if (curfilter->mode & 0x40)
     {
        // FAD Range Check
        if (Cs2Area->workblock.FAD < curfilter->FAD ||
            Cs2Area->workblock.FAD >= (curfilter->FAD+curfilter->range))
            condresults = 0;
     }

     if (condresults == 1)
     {
        Cs2Area->lastbuffer = curfilter->condtrue;
        fltpartition = &Cs2Area->partition[curfilter->condtrue];
        break;
     }
     else
     {
        Cs2Area->lastbuffer = curfilter->condfalse;

        if (curfilter->condfalse == 0xFF)
           return NULL;
        // loop and try filter that was connected to the false connector
        curfilter = &Cs2Area->filter[curfilter->condfalse];
     }
  }

  // Allocate block
  fltpartition->block[fltpartition->numblocks] = Cs2AllocateBlock(&fltpartition->blocknum[fltpartition->numblocks]);

  if (fltpartition->block[fltpartition->numblocks] == NULL)
    return NULL;

  // Copy workblock settings to allocated block
  fltpartition->block[fltpartition->numblocks]->size = Cs2Area->workblock.size;
  fltpartition->block[fltpartition->numblocks]->FAD = Cs2Area->workblock.FAD;
  fltpartition->block[fltpartition->numblocks]->cn = Cs2Area->workblock.cn;
  fltpartition->block[fltpartition->numblocks]->fn = Cs2Area->workblock.fn;
  fltpartition->block[fltpartition->numblocks]->sm = Cs2Area->workblock.sm;
  fltpartition->block[fltpartition->numblocks]->ci = Cs2Area->workblock.ci;

  // convert raw sector to type specified in getsectsize
  switch(Cs2Area->workblock.size)
  {
     case 2048: // user data only
                if (Cs2Area->workblock.data[0xF] == 0x02)
                   // m2f1
                   memcpy(fltpartition->block[fltpartition->numblocks]->data,
                          Cs2Area->workblock.data + 24, Cs2Area->workblock.size);
                else
                   // m1
                   memcpy(fltpartition->block[fltpartition->numblocks]->data,
                             Cs2Area->workblock.data + 16, Cs2Area->workblock.size);
                break;
     case 2324: // m2f2 user data only
                memcpy(fltpartition->block[fltpartition->numblocks]->data,
                       Cs2Area->workblock.data + 24, Cs2Area->workblock.size);
                break;
     case 2336: // m2f2 skip sync+header data
                memcpy(fltpartition->block[fltpartition->numblocks]->data,
                Cs2Area->workblock.data + 16, Cs2Area->workblock.size);
                break;
     case 2340: // m2f2 skip sync data
                memcpy(fltpartition->block[fltpartition->numblocks]->data,
                Cs2Area->workblock.data + 12, Cs2Area->workblock.size);
                break;
     case 2352: // Copy data as is
                memcpy(fltpartition->block[fltpartition->numblocks]->data,
                       Cs2Area->workblock.data, Cs2Area->workblock.size);
                break;
     default: break;
  }

  // Modify Partition values
  if (fltpartition->size == -1) fltpartition->size = 0;
  fltpartition->size += fltpartition->block[fltpartition->numblocks]->size;
  fltpartition->numblocks++;

  return fltpartition;
}