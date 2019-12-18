#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  void* m68k_reg ;
struct TYPE_9__ {int /*<<< orphan*/  ir; } ;
typedef  TYPE_1__ m68k_info ;
struct TYPE_10__ {void* reg; } ;
typedef  TYPE_2__ cs_m68k_op ;
struct TYPE_11__ {TYPE_2__* operands; } ;
typedef  TYPE_3__ cs_m68k ;

/* Variables and functions */
 scalar_t__ BIT_1 (int /*<<< orphan*/ ) ; 
 scalar_t__ BIT_F (int) ; 
 int /*<<< orphan*/  LIMIT_CPU_TYPES (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68010_PLUS ; 
 int /*<<< orphan*/  M68K_INS_MOVEC ; 
 void* M68K_REG_A0 ; 
 void* M68K_REG_CAAR ; 
 void* M68K_REG_CACR ; 
 void* M68K_REG_D0 ; 
 void* M68K_REG_DFC ; 
 void* M68K_REG_DTT0 ; 
 void* M68K_REG_DTT1 ; 
 void* M68K_REG_INVALID ; 
 void* M68K_REG_ISP ; 
 void* M68K_REG_ITT0 ; 
 void* M68K_REG_ITT1 ; 
 void* M68K_REG_MMUSR ; 
 void* M68K_REG_MSP ; 
 void* M68K_REG_SFC ; 
 void* M68K_REG_SRP ; 
 void* M68K_REG_TC ; 
 void* M68K_REG_URP ; 
 void* M68K_REG_USP ; 
 void* M68K_REG_VBR ; 
 TYPE_3__* build_init_op (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int read_imm_16 (TYPE_1__*) ; 

__attribute__((used)) static void d68010_movec(m68k_info *info)
{
	uint extension;
	m68k_reg reg;
	cs_m68k* ext;
	cs_m68k_op* op0;
	cs_m68k_op* op1;


	LIMIT_CPU_TYPES(info, M68010_PLUS);

	extension = read_imm_16(info);
	reg = M68K_REG_INVALID;

	ext = build_init_op(info, M68K_INS_MOVEC, 2, 0);

	op0 = &ext->operands[0];
	op1 = &ext->operands[1];

	switch (extension & 0xfff) {
		case 0x000: reg = M68K_REG_SFC; break;
		case 0x001: reg = M68K_REG_DFC; break;
		case 0x800: reg = M68K_REG_USP; break;
		case 0x801: reg = M68K_REG_VBR; break;
		case 0x002: reg = M68K_REG_CACR; break;
		case 0x802: reg = M68K_REG_CAAR; break;
		case 0x803: reg = M68K_REG_MSP; break;
		case 0x804: reg = M68K_REG_ISP; break;
		case 0x003: reg = M68K_REG_TC; break;
		case 0x004: reg = M68K_REG_ITT0; break;
		case 0x005: reg = M68K_REG_ITT1; break;
		case 0x006: reg = M68K_REG_DTT0; break;
		case 0x007: reg = M68K_REG_DTT1; break;
		case 0x805: reg = M68K_REG_MMUSR; break;
		case 0x806: reg = M68K_REG_URP; break;
		case 0x807: reg = M68K_REG_SRP; break;
	}

	if (BIT_1(info->ir)) {
		op0->reg = (BIT_F(extension) ? M68K_REG_A0 : M68K_REG_D0) + ((extension >> 12) & 7);
		op1->reg = reg;
	} else {
		op0->reg = reg;
		op1->reg = (BIT_F(extension) ? M68K_REG_A0 : M68K_REG_D0) + ((extension >> 12) & 7);
	}
}