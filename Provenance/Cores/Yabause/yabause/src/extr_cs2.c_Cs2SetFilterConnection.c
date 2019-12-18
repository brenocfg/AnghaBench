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
typedef  size_t u8 ;
struct TYPE_5__ {int CR3; int CR1; int CR2; int HIRQ; } ;
struct TYPE_6__ {TYPE_2__ reg; int /*<<< orphan*/  status; TYPE_1__* filter; } ;
struct TYPE_4__ {int condtrue; int condfalse; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_ESEL ; 
 TYPE_3__* Cs2Area ; 
 int /*<<< orphan*/  doCDReport (int /*<<< orphan*/ ) ; 

void Cs2SetFilterConnection(void) {
  u8 sfcfilternum;

  sfcfilternum = Cs2Area->reg.CR3 >> 8;

  if (Cs2Area->reg.CR1 & 0x1)
  {
     // Set connection for true condition
     Cs2Area->filter[sfcfilternum].condtrue = Cs2Area->reg.CR2 >> 8;
  }

  if (Cs2Area->reg.CR1 & 0x2)
  {
     // Set connection for false condition
     Cs2Area->filter[sfcfilternum].condfalse = Cs2Area->reg.CR2 & 0xFF;
  }

  doCDReport(Cs2Area->status);
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_ESEL;
}