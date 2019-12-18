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
typedef  scalar_t__ u16 ;
struct TYPE_7__ {scalar_t__ CR2; int CR3; scalar_t__ CR4; int HIRQ; } ;
struct TYPE_8__ {TYPE_3__ reg; int /*<<< orphan*/  status; scalar_t__ calcsize; TYPE_2__* partition; } ;
struct TYPE_6__ {scalar_t__ size; TYPE_1__** block; } ;
struct TYPE_5__ {int size; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_ESEL ; 
 TYPE_4__* Cs2Area ; 
 int /*<<< orphan*/  doCDReport (int /*<<< orphan*/ ) ; 

void Cs2CalculateActualSize(void) {
  u16 i;
  u32 casbufno;
  u16 cassectoffset;
  u16 casnumsect;

  cassectoffset = Cs2Area->reg.CR2;
  casbufno = Cs2Area->reg.CR3 >> 8;
  casnumsect = Cs2Area->reg.CR4;

  if (Cs2Area->partition[casbufno].size != 0)
  {
     Cs2Area->calcsize = 0;

     for (i = 0; i < casnumsect; i++)
     {
        if (Cs2Area->partition[casbufno].block[cassectoffset])
           Cs2Area->calcsize += (Cs2Area->partition[casbufno].block[cassectoffset]->size / 2);
     }
  }
  else
     Cs2Area->calcsize = 0;

  doCDReport(Cs2Area->status);
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_ESEL;
}