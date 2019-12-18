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
struct TYPE_4__ {int CR1; int CR2; int CR3; int CR4; int HIRQ; } ;
struct TYPE_6__ {int status; TYPE_1__ reg; scalar_t__ infotranstype; scalar_t__ transfercount; int /*<<< orphan*/  TOC; TYPE_2__* cdi; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ReadTOC ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_DRDY ; 
 int CDB_STAT_PAUSE ; 
 TYPE_3__* Cs2Area ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void Cs2GetToc(void) {
  Cs2Area->cdi->ReadTOC(Cs2Area->TOC);

  Cs2Area->transfercount = 0;
  Cs2Area->infotranstype = 0;

  Cs2Area->reg.CR1 = Cs2Area->status << 8;
  Cs2Area->reg.CR2 = 0xCC;
  Cs2Area->reg.CR3 = 0x0;
  Cs2Area->reg.CR4 = 0x0;
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_DRDY;
  Cs2Area->status = CDB_STAT_PAUSE;
}