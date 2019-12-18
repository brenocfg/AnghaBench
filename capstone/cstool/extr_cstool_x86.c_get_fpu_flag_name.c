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
typedef  int uint64_t ;

/* Variables and functions */
#define  X86_FPU_FLAGS_MODIFY_C0 147 
#define  X86_FPU_FLAGS_MODIFY_C1 146 
#define  X86_FPU_FLAGS_MODIFY_C2 145 
#define  X86_FPU_FLAGS_MODIFY_C3 144 
#define  X86_FPU_FLAGS_RESET_C0 143 
#define  X86_FPU_FLAGS_RESET_C1 142 
#define  X86_FPU_FLAGS_RESET_C2 141 
#define  X86_FPU_FLAGS_RESET_C3 140 
#define  X86_FPU_FLAGS_SET_C0 139 
#define  X86_FPU_FLAGS_SET_C1 138 
#define  X86_FPU_FLAGS_SET_C2 137 
#define  X86_FPU_FLAGS_SET_C3 136 
#define  X86_FPU_FLAGS_TEST_C0 135 
#define  X86_FPU_FLAGS_TEST_C1 134 
#define  X86_FPU_FLAGS_TEST_C2 133 
#define  X86_FPU_FLAGS_TEST_C3 132 
#define  X86_FPU_FLAGS_UNDEFINED_C0 131 
#define  X86_FPU_FLAGS_UNDEFINED_C1 130 
#define  X86_FPU_FLAGS_UNDEFINED_C2 129 
#define  X86_FPU_FLAGS_UNDEFINED_C3 128 

__attribute__((used)) static const char *get_fpu_flag_name(uint64_t flag)
{
	switch (flag) {
		default:
			return NULL;
		case X86_FPU_FLAGS_MODIFY_C0:
			return "MOD_C0";
		case X86_FPU_FLAGS_MODIFY_C1:
			return "MOD_C1";
		case X86_FPU_FLAGS_MODIFY_C2:
			return "MOD_C2";
		case X86_FPU_FLAGS_MODIFY_C3:
			return "MOD_C3";
		case X86_FPU_FLAGS_RESET_C0:
			return "RESET_C0";
		case X86_FPU_FLAGS_RESET_C1:
			return "RESET_C1";
		case X86_FPU_FLAGS_RESET_C2:
			return "RESET_C2";
		case X86_FPU_FLAGS_RESET_C3:
			return "RESET_C3";
		case X86_FPU_FLAGS_SET_C0:
			return "SET_C0";
		case X86_FPU_FLAGS_SET_C1:
			return "SET_C1";
		case X86_FPU_FLAGS_SET_C2:
			return "SET_C2";
		case X86_FPU_FLAGS_SET_C3:
			return "SET_C3";
		case X86_FPU_FLAGS_UNDEFINED_C0:
			return "UNDEF_C0";
		case X86_FPU_FLAGS_UNDEFINED_C1:
			return "UNDEF_C1";
		case X86_FPU_FLAGS_UNDEFINED_C2:
			return "UNDEF_C2";
		case X86_FPU_FLAGS_UNDEFINED_C3:
			return "UNDEF_C3";
		case X86_FPU_FLAGS_TEST_C0:
			return "TEST_C0";
		case X86_FPU_FLAGS_TEST_C1:
			return "TEST_C1";
		case X86_FPU_FLAGS_TEST_C2:
			return "TEST_C2";
		case X86_FPU_FLAGS_TEST_C3:
			return "TEST_C3";
	}
}