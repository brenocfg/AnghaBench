#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int high; char low; } ;
struct TYPE_12__ {int AGX; int AGR_Z; } ;
struct TYPE_13__ {char reg; TYPE_1__ bitreg; } ;
struct TYPE_14__ {TYPE_2__ cr4; } ;
struct TYPE_15__ {TYPE_3__ SOP; } ;
struct TYPE_16__ {TYPE_4__ SOP_REGS; } ;
struct TYPE_17__ {int daa_mode; TYPE_5__ m_DAAShadowRegs; } ;
typedef  TYPE_6__ IXJ ;
typedef  TYPE_7__ BYTES ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_Prepare (TYPE_6__*) ; 
#define  SOP_PU_CONVERSATION 131 
#define  SOP_PU_PULSEDIALING 130 
#define  SOP_PU_RINGING 129 
#define  SOP_PU_SLEEP 128 
 int /*<<< orphan*/  daa_load (TYPE_7__*,TYPE_6__*) ; 

__attribute__((used)) static int ixj_daa_cr4(IXJ *j, char reg)
{
	BYTES bytes;

	switch (j->daa_mode) {
	case SOP_PU_SLEEP:
		bytes.high = 0x14;
		break;
	case SOP_PU_RINGING:
		bytes.high = 0x54;
		break;
	case SOP_PU_CONVERSATION:
		bytes.high = 0x94;
		break;
	case SOP_PU_PULSEDIALING:
		bytes.high = 0xD4;
		break;
	}

	j->m_DAAShadowRegs.SOP_REGS.SOP.cr4.reg = reg;

	switch (j->m_DAAShadowRegs.SOP_REGS.SOP.cr4.bitreg.AGX) {
	case 0:
		j->m_DAAShadowRegs.SOP_REGS.SOP.cr4.bitreg.AGR_Z = 0;
		break;
	case 1:
		j->m_DAAShadowRegs.SOP_REGS.SOP.cr4.bitreg.AGR_Z = 2;
		break;
	case 2:
		j->m_DAAShadowRegs.SOP_REGS.SOP.cr4.bitreg.AGR_Z = 1;
		break;
	case 3:
		j->m_DAAShadowRegs.SOP_REGS.SOP.cr4.bitreg.AGR_Z = 3;
		break;
	}

	bytes.low = j->m_DAAShadowRegs.SOP_REGS.SOP.cr4.reg;

	if (!daa_load(&bytes, j))
		return 0;

	if (!SCI_Prepare(j))
		return 0;

	return 1;
}