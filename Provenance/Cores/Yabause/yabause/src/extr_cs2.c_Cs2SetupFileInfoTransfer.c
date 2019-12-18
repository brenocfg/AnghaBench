#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  size_t u32 ;
struct TYPE_4__ {TYPE_1__* fileinfo; void** transfileinfo; } ;
struct TYPE_3__ {int lba; int size; void* flags; void* fileunitsize; void* interleavegapsize; } ;

/* Variables and functions */
 TYPE_2__* Cs2Area ; 

void Cs2SetupFileInfoTransfer(u32 fid) {
  Cs2Area->transfileinfo[0] = (u8)(Cs2Area->fileinfo[fid].lba >> 24);
  Cs2Area->transfileinfo[1] = (u8)(Cs2Area->fileinfo[fid].lba >> 16);
  Cs2Area->transfileinfo[2] = (u8)(Cs2Area->fileinfo[fid].lba >> 8);
  Cs2Area->transfileinfo[3] = (u8)Cs2Area->fileinfo[fid].lba;

  Cs2Area->transfileinfo[4] = (u8)(Cs2Area->fileinfo[fid].size >> 24);
  Cs2Area->transfileinfo[5] = (u8)(Cs2Area->fileinfo[fid].size >> 16);
  Cs2Area->transfileinfo[6] = (u8)(Cs2Area->fileinfo[fid].size >> 8);
  Cs2Area->transfileinfo[7] = (u8)Cs2Area->fileinfo[fid].size;

  Cs2Area->transfileinfo[8] = Cs2Area->fileinfo[fid].interleavegapsize;
  Cs2Area->transfileinfo[9] = Cs2Area->fileinfo[fid].fileunitsize;
  Cs2Area->transfileinfo[10] = (u8) fid;
  Cs2Area->transfileinfo[11] = Cs2Area->fileinfo[fid].flags;
}