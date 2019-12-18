#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  void* u16 ;
struct TYPE_7__ {int CR2; int CR3; int CR1; int CR4; int HIRQ; } ;
struct TYPE_8__ {int status; TYPE_3__ reg; TYPE_2__* partition; } ;
struct TYPE_6__ {size_t numblocks; TYPE_1__** block; } ;
struct TYPE_5__ {int FAD; int fn; int cn; int sm; int ci; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_ESEL ; 
 int CDB_STAT_REJECT ; 
 int /*<<< orphan*/  CDLOG (char*) ; 
 TYPE_4__* Cs2Area ; 
 size_t MAX_SELECTORS ; 

void Cs2GetSectorInfo(void) {
  u32 gsisctnum;
  u32 gsibufno;

  gsisctnum = Cs2Area->reg.CR2 & 0xFF;
  gsibufno = Cs2Area->reg.CR3 >> 8;
  if (gsibufno < MAX_SELECTORS) {
     if (gsisctnum < Cs2Area->partition[gsibufno].numblocks) {
        Cs2Area->reg.CR1 = (u16)((Cs2Area->status << 8) | ((Cs2Area->partition[gsibufno].block[gsisctnum]->FAD >> 16) & 0xFF));
        Cs2Area->reg.CR2 = (u16)Cs2Area->partition[gsibufno].block[gsisctnum]->FAD;
        Cs2Area->reg.CR3 = (Cs2Area->partition[gsibufno].block[gsisctnum]->fn << 8) | Cs2Area->partition[gsibufno].block[gsisctnum]->cn;
        Cs2Area->reg.CR4 = (Cs2Area->partition[gsibufno].block[gsisctnum]->sm << 8) | Cs2Area->partition[gsibufno].block[gsisctnum]->ci;
        Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_ESEL;
        return;
     }
     else
     {
        CDLOG("cs2\t: getSectorInfo: Unsupported Partition Number\n");
     }
  }

  Cs2Area->reg.CR1 = (CDB_STAT_REJECT << 8) | (Cs2Area->reg.CR1 & 0xFF);
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_ESEL;
}