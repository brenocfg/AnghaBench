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
struct TYPE_5__ {int CR3; int CR1; int HIRQ; } ;
struct TYPE_6__ {TYPE_2__ reg; int /*<<< orphan*/  status; TYPE_1__* filter; } ;
struct TYPE_4__ {int mode; scalar_t__ cival; scalar_t__ smval; scalar_t__ cimask; scalar_t__ smmask; scalar_t__ chan; scalar_t__ range; scalar_t__ FAD; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_ESEL ; 
 TYPE_3__* Cs2Area ; 
 int /*<<< orphan*/  doCDReport (int /*<<< orphan*/ ) ; 

void Cs2SetFilterMode(void) {
  u8 sfmfilternum;

  sfmfilternum = Cs2Area->reg.CR3 >> 8;

  Cs2Area->filter[sfmfilternum].mode = Cs2Area->reg.CR1 & 0xFF;

  if (Cs2Area->filter[sfmfilternum].mode & 0x80)
  {
     // Initialize filter conditions
     Cs2Area->filter[sfmfilternum].mode = 0;
     Cs2Area->filter[sfmfilternum].FAD = 0;
     Cs2Area->filter[sfmfilternum].range = 0;
     Cs2Area->filter[sfmfilternum].chan = 0;
     Cs2Area->filter[sfmfilternum].smmask = 0;
     Cs2Area->filter[sfmfilternum].cimask = 0;
     Cs2Area->filter[sfmfilternum].smval = 0;
     Cs2Area->filter[sfmfilternum].cival = 0;
  }

  doCDReport(Cs2Area->status);
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_ESEL;
}