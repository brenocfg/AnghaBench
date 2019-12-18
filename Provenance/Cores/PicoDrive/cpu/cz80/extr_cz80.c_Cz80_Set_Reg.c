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
struct TYPE_3__ {size_t BasePC; size_t* Fetch; size_t PC; size_t HaltState; size_t IRQState; int /*<<< orphan*/ * OPFetch; int /*<<< orphan*/  OPBase; } ;
typedef  TYPE_1__ cz80_struc ;
typedef  size_t UINT32 ;
typedef  int INT32 ;

/* Variables and functions */
#define  CZ80_AF 146 
#define  CZ80_AF2 145 
#define  CZ80_BC 144 
#define  CZ80_BC2 143 
#define  CZ80_DE 142 
#define  CZ80_DE2 141 
 size_t CZ80_FETCH_SFT ; 
#define  CZ80_HALT 140 
#define  CZ80_HL 139 
#define  CZ80_HL2 138 
#define  CZ80_I 137 
#define  CZ80_IFF1 136 
#define  CZ80_IFF2 135 
#define  CZ80_IM 134 
#define  CZ80_IRQ 133 
#define  CZ80_IX 132 
#define  CZ80_IY 131 
#define  CZ80_PC 130 
#define  CZ80_R 129 
#define  CZ80_SP 128 
 size_t zAF ; 
 size_t zAF2 ; 
 size_t zBC ; 
 size_t zBC2 ; 
 size_t zDE ; 
 size_t zDE2 ; 
 size_t zHL ; 
 size_t zHL2 ; 
 size_t zI ; 
 int zIFF1 ; 
 int zIFF2 ; 
 size_t zIM ; 
 size_t zIX ; 
 size_t zIY ; 
 size_t zR ; 
 size_t zSP ; 

void Cz80_Set_Reg(cz80_struc *CPU, INT32 regnum, UINT32 val)
{
	switch (regnum)
	{
	case CZ80_PC:
		CPU->BasePC = CPU->Fetch[val >> CZ80_FETCH_SFT];
#if CZ80_ENCRYPTED_ROM
		CPU->OPBase = CPU->OPFetch[val >> CZ80_FETCH_SFT];
#endif
		CPU->PC = val + CPU->BasePC;
		break;

	case CZ80_SP:   zSP = val; break;
	case CZ80_AF:   zAF = val; break;
	case CZ80_BC:   zBC = val; break;
	case CZ80_DE:   zDE = val; break;
	case CZ80_HL:   zHL = val; break;
	case CZ80_IX:   zIX = val; break;
	case CZ80_IY:   zIY = val; break;
	case CZ80_AF2:  zAF2 = val; break;
	case CZ80_BC2:  zBC2 = val; break;
	case CZ80_DE2:  zDE2 = val; break;
	case CZ80_HL2:  zHL2 = val; break;
	case CZ80_R:    zR = val; break;
	case CZ80_I:    zI = val; break;
	case CZ80_IM:   zIM = val; break;
	case CZ80_IFF1: zIFF1 = val ? (1 << 2) : 0; break;
	case CZ80_IFF2: zIFF2 = val ? (1 << 2) : 0; break;
	case CZ80_HALT: CPU->HaltState = val; break;
	case CZ80_IRQ:  CPU->IRQState = val; break;
	default: break;
	}
}