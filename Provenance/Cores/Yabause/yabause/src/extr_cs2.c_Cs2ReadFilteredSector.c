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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  partition_struct ;
struct TYPE_5__ {int* data; int size; int fn; int cn; int sm; int ci; int /*<<< orphan*/  FAD; } ;
struct TYPE_6__ {int getsectsize; int isaudio; int /*<<< orphan*/ * outconcddev; TYPE_2__ workblock; TYPE_1__* cdi; int /*<<< orphan*/  isbufferfull; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ReadSectorFAD ) (int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 TYPE_3__* Cs2Area ; 
 int /*<<< orphan*/ * Cs2FilterData (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Cs2SetTiming (int) ; 
 int /*<<< orphan*/  ScspReceiveCDDA (int*) ; 
 scalar_t__ memcmp (char*,int*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*) ; 

int Cs2ReadFilteredSector(u32 rfsFAD, partition_struct **partition) {
  char syncheader[12] = { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                          0xFF, 0xFF, 0xFF, 0x00};
  int isaudio = 0;

  if (Cs2Area->outconcddev != NULL && !Cs2Area->isbufferfull)
  {
     // read a sector using cd interface function to workblock.data
     if (!Cs2Area->cdi->ReadSectorFAD(rfsFAD, Cs2Area->workblock.data))
     {
        *partition = NULL;
        return -2;
     }

     Cs2Area->workblock.size = Cs2Area->getsectsize;
     Cs2Area->workblock.FAD = rfsFAD;

     if (memcmp(syncheader, Cs2Area->workblock.data, 12) != 0) isaudio = 1;

     // force 1x speed if reading from an audio track
     Cs2Area->isaudio = isaudio;
     Cs2SetTiming(1);

     // if mode 2 track, setup the subheader values
     if (isaudio)
     {
        ScspReceiveCDDA(Cs2Area->workblock.data);
        *partition = NULL;
        return 0;
     }
     else if (Cs2Area->workblock.data[0xF] == 0x02)
     {
        // if it's form 2 data the sector size should be 2324
        if (Cs2Area->workblock.data[0x12] & 0x20) Cs2Area->workblock.size = 2324;

        Cs2Area->workblock.fn = Cs2Area->workblock.data[0x10];
        Cs2Area->workblock.cn = Cs2Area->workblock.data[0x11];
        Cs2Area->workblock.sm = Cs2Area->workblock.data[0x12];
        Cs2Area->workblock.ci = Cs2Area->workblock.data[0x13];
     }


     // pass workblock to filter function(after it identifies partition,
     // it should allocate the partition block, setup/change the partition
     // values, and copy workblock to the allocated block)
     *partition = Cs2FilterData(Cs2Area->outconcddev, isaudio);
     return 0;
  }

  *partition = NULL;
  return -1;
}