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
 size_t Rm ; 
 size_t Rn ; 
 char** regname ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static UINT32 op0110(char *buffer, UINT32 pc, UINT16 opcode)

{
	switch(opcode & 0xF)
	{
	case 0x00:
		sprintf(buffer, "MOV.B   @%s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x01:
		sprintf(buffer, "MOV.W   @%s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x02:
		sprintf(buffer, "MOV.L   @%s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x03:
		sprintf(buffer, "MOV     %s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x04:
		sprintf(buffer, "MOV.B   @%s+,%s", regname[Rm], regname[Rn]);
		break;
	case 0x05:
		sprintf(buffer, "MOV.W   @%s+,%s", regname[Rm], regname[Rn]);
		break;
	case 0x06:
		sprintf(buffer, "MOV.L   @%s+,%s", regname[Rm], regname[Rn]);
		break;
	case 0x07:
		sprintf(buffer, "NOT     %s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x08:
		sprintf(buffer, "SWAP.B  %s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x09:
		sprintf(buffer, "SWAP.W  %s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x0a:
		sprintf(buffer, "NEGC    %s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x0b:
		sprintf(buffer, "NEG     %s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x0c:
		sprintf(buffer, "EXTU.B  %s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x0d:
		sprintf(buffer, "EXTU.W  %s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x0e:
		sprintf(buffer, "EXTS.B  %s,%s", regname[Rm], regname[Rn]);
		break;
	case 0x0f:
		sprintf(buffer, "EXTS.W  %s,%s", regname[Rm], regname[Rn]);
		break;
	}
	return 0;
}