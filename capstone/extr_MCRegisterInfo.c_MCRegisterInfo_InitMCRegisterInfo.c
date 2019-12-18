#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {unsigned int NumRegs; unsigned int RAReg; unsigned int PCReg; char const* RegStrings; unsigned int NumClasses; unsigned int NumRegUnits; unsigned int NumSubRegIndices; int /*<<< orphan*/  const* RegEncodingTable; int /*<<< orphan*/  const* SubRegIndices; int /*<<< orphan*/ ** RegUnitRoots; int /*<<< orphan*/  const* DiffLists; int /*<<< orphan*/  const* Classes; int /*<<< orphan*/  const* Desc; } ;
typedef  TYPE_1__ MCRegisterInfo ;
typedef  int /*<<< orphan*/  MCRegisterDesc ;
typedef  int /*<<< orphan*/  MCRegisterClass ;
typedef  int /*<<< orphan*/  MCPhysReg ;

/* Variables and functions */

void MCRegisterInfo_InitMCRegisterInfo(MCRegisterInfo *RI,
		const MCRegisterDesc *D, unsigned NR,
		unsigned RA, unsigned PC,
		const MCRegisterClass *C, unsigned NC,
		uint16_t (*RURoots)[2], unsigned NRU,
		const MCPhysReg *DL,
		const char *Strings,
		const uint16_t *SubIndices, unsigned NumIndices,
		const uint16_t *RET)
{
	RI->Desc = D;
	RI->NumRegs = NR;
	RI->RAReg = RA;
	RI->PCReg = PC;
	RI->Classes = C;
	RI->DiffLists = DL;
	RI->RegStrings = Strings;
	RI->NumClasses = NC;
	RI->RegUnitRoots = RURoots;
	RI->NumRegUnits = NRU;
	RI->SubRegIndices = SubIndices;
	RI->NumSubRegIndices = NumIndices;
	RI->RegEncodingTable = RET;
}