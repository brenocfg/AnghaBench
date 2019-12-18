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
typedef  size_t u32 ;
struct TYPE_5__ {int CR3; int CR1; int HIRQ; scalar_t__ CR2; scalar_t__ CR4; } ;
struct TYPE_6__ {int status; TYPE_2__ reg; TYPE_1__* partition; } ;
struct TYPE_4__ {int size; scalar_t__ numblocks; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_DRDY ; 
 TYPE_3__* Cs2Area ; 

void Cs2GetSectorNumber(void) {
  u32 gsnbufno;

  gsnbufno = Cs2Area->reg.CR3 >> 8;

  if (Cs2Area->partition[gsnbufno].size == -1)
     Cs2Area->reg.CR4 = 0;
  else
     Cs2Area->reg.CR4 = Cs2Area->partition[gsnbufno].numblocks;

  Cs2Area->reg.CR1 = Cs2Area->status << 8;
  Cs2Area->reg.CR2 = 0;
  Cs2Area->reg.CR3 = 0;
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_DRDY;
}