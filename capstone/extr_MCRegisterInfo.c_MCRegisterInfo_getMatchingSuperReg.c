#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {unsigned int NumRegs; TYPE_1__* Desc; scalar_t__ DiffLists; } ;
struct TYPE_5__ {scalar_t__ SuperRegs; } ;
typedef  TYPE_2__ MCRegisterInfo ;
typedef  int /*<<< orphan*/  MCRegisterClass ;
typedef  int /*<<< orphan*/  MCPhysReg ;
typedef  int /*<<< orphan*/  DiffListIterator ;

/* Variables and functions */
 int DiffListIterator_getVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DiffListIterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DiffListIterator_isValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DiffListIterator_next (int /*<<< orphan*/ *) ; 
 scalar_t__ MCRegisterClass_contains (int /*<<< orphan*/  const*,int) ; 
 unsigned int MCRegisterInfo_getSubReg (TYPE_2__ const*,int,unsigned int) ; 

unsigned MCRegisterInfo_getMatchingSuperReg(const MCRegisterInfo *RI, unsigned Reg, unsigned SubIdx, const MCRegisterClass *RC)
{
	DiffListIterator iter;

	if (Reg >= RI->NumRegs) {
		return 0;
	}

	DiffListIterator_init(&iter, (MCPhysReg)Reg, RI->DiffLists + RI->Desc[Reg].SuperRegs);
	DiffListIterator_next(&iter);

	while(DiffListIterator_isValid(&iter)) {
		uint16_t val = DiffListIterator_getVal(&iter);
		if (MCRegisterClass_contains(RC, val) && Reg ==  MCRegisterInfo_getSubReg(RI, val, SubIdx))
			return val;

		DiffListIterator_next(&iter);
	}

	return 0;
}