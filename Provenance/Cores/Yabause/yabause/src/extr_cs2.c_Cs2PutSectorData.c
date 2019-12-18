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
typedef  int u32 ;
struct TYPE_3__ {int CR3; int HIRQ; } ;
struct TYPE_4__ {TYPE_1__ reg; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_EHST ; 
 int /*<<< orphan*/  CDB_STAT_REJECT ; 
 TYPE_2__* Cs2Area ; 
 int MAX_SELECTORS ; 
 int /*<<< orphan*/  doCDReport (int /*<<< orphan*/ ) ; 

void Cs2PutSectorData(void) {
  u32 psdfiltno;

  psdfiltno = Cs2Area->reg.CR3 >> 8;

  if (psdfiltno < MAX_SELECTORS)
  {
     // I'm not really sure what I'm supposed to really be doing or returning
     Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_EHST;
  }
  else
  {
     doCDReport(CDB_STAT_REJECT);
     Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_EHST;
  }
}