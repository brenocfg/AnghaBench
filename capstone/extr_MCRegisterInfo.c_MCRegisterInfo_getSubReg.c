#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint16_t ;
struct TYPE_5__ {unsigned int* SubRegIndices; TYPE_1__* Desc; scalar_t__ DiffLists; } ;
struct TYPE_4__ {int SubRegIndices; scalar_t__ SubRegs; } ;
typedef  TYPE_2__ MCRegisterInfo ;
typedef  int /*<<< orphan*/  MCPhysReg ;
typedef  int /*<<< orphan*/  DiffListIterator ;

/* Variables and functions */
 int DiffListIterator_getVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DiffListIterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DiffListIterator_isValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DiffListIterator_next (int /*<<< orphan*/ *) ; 

unsigned MCRegisterInfo_getSubReg(const MCRegisterInfo *RI, unsigned Reg, unsigned Idx)
{
	DiffListIterator iter;
	const uint16_t *SRI = RI->SubRegIndices + RI->Desc[Reg].SubRegIndices;

	DiffListIterator_init(&iter, (MCPhysReg)Reg, RI->DiffLists + RI->Desc[Reg].SubRegs);
	DiffListIterator_next(&iter);

	while(DiffListIterator_isValid(&iter)) {
		if (*SRI == Idx)
			return DiffListIterator_getVal(&iter);
		DiffListIterator_next(&iter);
		++SRI;
	}

	return 0;
}