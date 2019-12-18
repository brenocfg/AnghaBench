#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct SStream {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {size_t ins; int am; } ;
struct TYPE_7__ {unsigned char Opcode; int /*<<< orphan*/  address; TYPE_1__* Operands; } ;
struct TYPE_6__ {unsigned int ImmVal; } ;
typedef  TYPE_2__ MCInst ;

/* Variables and functions */
 TYPE_5__* InstructionInfoTable ; 
#define  MOS65XX_AM_ABS 140 
#define  MOS65XX_AM_ABSX 139 
#define  MOS65XX_AM_ABSY 138 
#define  MOS65XX_AM_ACC 137 
#define  MOS65XX_AM_IMM 136 
#define  MOS65XX_AM_IMP 135 
#define  MOS65XX_AM_IND 134 
#define  MOS65XX_AM_INDX 133 
#define  MOS65XX_AM_INDY 132 
#define  MOS65XX_AM_REL 131 
#define  MOS65XX_AM_ZP 130 
#define  MOS65XX_AM_ZPX 129 
#define  MOS65XX_AM_ZPY 128 
 TYPE_3__* OpInfoTable ; 
 int /*<<< orphan*/  SStream_concat (struct SStream*,char*,...) ; 
 int /*<<< orphan*/  SStream_concat0 (struct SStream*,int /*<<< orphan*/ ) ; 

void MOS65XX_printInst(MCInst *MI, struct SStream *O, void *PrinterInfo)
{
#ifndef CAPSTONE_DIET
	unsigned char opcode = MI->Opcode;

	SStream_concat0(O, InstructionInfoTable[OpInfoTable[MI->Opcode].ins].name);
	unsigned int value = MI->Operands[0].ImmVal;

	switch (OpInfoTable[opcode].am) {
		default:
			break;

		case MOS65XX_AM_IMP:
			break;

		case MOS65XX_AM_ACC:
			SStream_concat(O, " a");
			break;

		case MOS65XX_AM_ABS:
			SStream_concat(O, " $0x%04x", value);
			break;

		case MOS65XX_AM_IMM:
			SStream_concat(O, " #$0x%02x", value);
			break;

		case MOS65XX_AM_ZP:
			SStream_concat(O, " $0x%02x", value);
			break;

		case MOS65XX_AM_ABSX:
			SStream_concat(O, " $0x%04x, x", value);
			break;

		case MOS65XX_AM_ABSY:
			SStream_concat(O, " $0x%04x, y", value);
			break;

		case MOS65XX_AM_ZPX:
			SStream_concat(O, " $0x%02x, x", value);
			break;

		case MOS65XX_AM_ZPY:
			SStream_concat(O, " $0x%02x, y", value);
			break;

		case MOS65XX_AM_REL:
			SStream_concat(O, " $0x%04x", MI->address + (signed char) value + 2);
			break;

		case MOS65XX_AM_IND:
			SStream_concat(O, " ($0x%04x)", value);
			break;

		case MOS65XX_AM_INDX:
			SStream_concat(O, " ($0x%02x, x)", value);
			break;

		case MOS65XX_AM_INDY:
			SStream_concat(O, " ($0x%02x), y", value);
			break;
	}
#endif
}