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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_3__ {int CR3; int HIRQ; } ;
struct TYPE_4__ {TYPE_1__ reg; int /*<<< orphan*/  status; scalar_t__ outconcddevnum; int /*<<< orphan*/ * filter; int /*<<< orphan*/ * outconcddev; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_ESEL ; 
 TYPE_2__* Cs2Area ; 
 int /*<<< orphan*/  doCDReport (int /*<<< orphan*/ ) ; 

void Cs2SetCDDeviceConnection(void) {
  u32 scdcfilternum;

  scdcfilternum = (Cs2Area->reg.CR3 >> 8);

  if (scdcfilternum == 0xFF)
     Cs2Area->outconcddev = NULL;
  else if (scdcfilternum < 0x24)
     Cs2Area->outconcddev = Cs2Area->filter + scdcfilternum;

  Cs2Area->outconcddevnum = (u8)scdcfilternum;

  doCDReport(Cs2Area->status);
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_ESEL;
}