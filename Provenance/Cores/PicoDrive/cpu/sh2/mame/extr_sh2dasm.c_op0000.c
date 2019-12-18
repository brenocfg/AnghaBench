#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  DASMFLAG_STEP_OUT ; 
 size_t Rm ; 
 size_t Rn ; 
 char** regname ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static UINT32 op0000(char *buffer, UINT32 pc, UINT16 opcode)
{
	UINT32  flags = 0;
	switch(opcode & 0x3f)
	{
	case 0x02:
		sprintf(buffer,"STC     SR,%s", regname[Rn]);
		break;
	case 0x03:
		sprintf(buffer,"BSRF    %s", regname[Rn]);
		break;
	case 0x08:
		sprintf(buffer,"CLRT");
		break;
	case 0x09:
		sprintf(buffer,"NOP");
		break;
	case 0x0A:
		sprintf(buffer,"STS     MACH,%s", regname[Rn]);
		break;
	case 0x0B:
		sprintf(buffer,"RTS");
		flags = DASMFLAG_STEP_OUT;
		break;
	case 0x12:
		sprintf(buffer,"STS     GBR,%s", regname[Rn]);
		break;
	case 0x18:
		sprintf(buffer,"SETT");
		break;
	case 0x19:
		sprintf(buffer,"DIV0U");
		break;
	case 0x1A:
		sprintf(buffer,"STS     MACL,%s", regname[Rn]);
		break;
	case 0x1B:
		sprintf(buffer,"SLEEP");
		break;
	case 0x22:
		sprintf(buffer,"STC     VBR,%s", regname[Rn]);
		break;
	case 0x23:
		sprintf(buffer,"BRAF    %s", regname[Rn]);
		break;
	case 0x28:
		sprintf(buffer,"CLRMAC");
		break;
	case 0x29:
		sprintf(buffer,"MOVT    %s", regname[Rn]);
		break;
	case 0x2A:
		sprintf(buffer,"STS     PR,%s", regname[Rn]);
		break;
	case 0x2B:
		sprintf(buffer,"RTE");
		flags = DASMFLAG_STEP_OUT;
		break;
	default:
		switch(opcode & 15)
		{
		case  0:
			sprintf(buffer, "??????  $%04X", opcode);
			break;
		case  1:
			sprintf(buffer, "??????  $%04X", opcode);
			break;
		case  2:
			sprintf(buffer, "??????  $%04X", opcode);
			break;
		case  3:
			sprintf(buffer, "??????  $%04X", opcode);
			break;
		case  4:
			sprintf(buffer, "MOV.B   %s,@(R0,%s)", regname[Rm], regname[Rn]);
			break;
		case  5:
			sprintf(buffer, "MOV.W   %s,@(R0,%s)", regname[Rm], regname[Rn]);
			break;
		case  6:
			sprintf(buffer, "MOV.L   %s,@(R0,%s)", regname[Rm], regname[Rn]);
			break;
		case  7:
			sprintf(buffer, "MUL.L   %s,%s", regname[Rm], regname[Rn]);
			break;
		case  8:
			sprintf(buffer, "??????  $%04X", opcode);
			break;
		case  9:
			sprintf(buffer, "??????  $%04X", opcode);
			break;
		case 10:
			sprintf(buffer, "??????  $%04X", opcode);
			break;
		case 11:
			sprintf(buffer, "??????  $%04X", opcode);
			break;
		case 12:
			sprintf(buffer, "MOV.B   @(R0,%s),%s", regname[Rm], regname[Rn]);
			break;
		case 13:
			sprintf(buffer, "MOV.W   @(R0,%s),%s", regname[Rm], regname[Rn]);
			break;
		case 14:
			sprintf(buffer, "MOV.L   @(R0,%s),%s", regname[Rm], regname[Rn]);
			break;
		case 15:
			sprintf(buffer, "MAC.L   @%s+,@%s+", regname[Rn], regname[Rm]);
			break;
		}
	}
	return flags;
}