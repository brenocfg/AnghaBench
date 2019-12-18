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

/* Variables and functions */
 int EINVAL ; 
 int PERF_REG_X86_AX ; 
 int PERF_REG_X86_BP ; 
 int PERF_REG_X86_BX ; 
 int PERF_REG_X86_CX ; 
 int PERF_REG_X86_DI ; 
 int PERF_REG_X86_DX ; 
 int PERF_REG_X86_IP ; 
 int PERF_REG_X86_SI ; 
 int PERF_REG_X86_SP ; 
#define  UNW_X86_EAX 136 
#define  UNW_X86_EBP 135 
#define  UNW_X86_EBX 134 
#define  UNW_X86_ECX 133 
#define  UNW_X86_EDI 132 
#define  UNW_X86_EDX 131 
#define  UNW_X86_EIP 130 
#define  UNW_X86_ESI 129 
#define  UNW_X86_ESP 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int unwind__arch_reg_id(int regnum)
{
	int id;

	switch (regnum) {
	case UNW_X86_EAX:
		id = PERF_REG_X86_AX;
		break;
	case UNW_X86_EDX:
		id = PERF_REG_X86_DX;
		break;
	case UNW_X86_ECX:
		id = PERF_REG_X86_CX;
		break;
	case UNW_X86_EBX:
		id = PERF_REG_X86_BX;
		break;
	case UNW_X86_ESI:
		id = PERF_REG_X86_SI;
		break;
	case UNW_X86_EDI:
		id = PERF_REG_X86_DI;
		break;
	case UNW_X86_EBP:
		id = PERF_REG_X86_BP;
		break;
	case UNW_X86_ESP:
		id = PERF_REG_X86_SP;
		break;
	case UNW_X86_EIP:
		id = PERF_REG_X86_IP;
		break;
	default:
		pr_err("unwind: invalid reg id %d\n", regnum);
		return -EINVAL;
	}

	return id;
}