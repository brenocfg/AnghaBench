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
#define  EM_386 131 
#define  EM_IAMCU 130 
#define  EM_RISCV 129 
#define  EM_X86_64 128 

__attribute__((used)) static const char *
dwarf_reg(unsigned int mach, unsigned int reg)
{

	switch (mach) {
	case EM_386:
	case EM_IAMCU:
		switch (reg) {
		case 0: return "eax";
		case 1: return "ecx";
		case 2: return "edx";
		case 3: return "ebx";
		case 4: return "esp";
		case 5: return "ebp";
		case 6: return "esi";
		case 7: return "edi";
		case 8: return "eip";
		case 9: return "eflags";
		case 11: return "st0";
		case 12: return "st1";
		case 13: return "st2";
		case 14: return "st3";
		case 15: return "st4";
		case 16: return "st5";
		case 17: return "st6";
		case 18: return "st7";
		case 21: return "xmm0";
		case 22: return "xmm1";
		case 23: return "xmm2";
		case 24: return "xmm3";
		case 25: return "xmm4";
		case 26: return "xmm5";
		case 27: return "xmm6";
		case 28: return "xmm7";
		case 29: return "mm0";
		case 30: return "mm1";
		case 31: return "mm2";
		case 32: return "mm3";
		case 33: return "mm4";
		case 34: return "mm5";
		case 35: return "mm6";
		case 36: return "mm7";
		case 37: return "fcw";
		case 38: return "fsw";
		case 39: return "mxcsr";
		case 40: return "es";
		case 41: return "cs";
		case 42: return "ss";
		case 43: return "ds";
		case 44: return "fs";
		case 45: return "gs";
		case 48: return "tr";
		case 49: return "ldtr";
		default: return (NULL);
		}
	case EM_RISCV:
		switch (reg) {
		case 0: return "zero";
		case 1: return "ra";
		case 2: return "sp";
		case 3: return "gp";
		case 4: return "tp";
		case 5: return "t0";
		case 6: return "t1";
		case 7: return "t2";
		case 8: return "s0";
		case 9: return "s1";
		case 10: return "a0";
		case 11: return "a1";
		case 12: return "a2";
		case 13: return "a3";
		case 14: return "a4";
		case 15: return "a5";
		case 16: return "a6";
		case 17: return "a7";
		case 18: return "s2";
		case 19: return "s3";
		case 20: return "s4";
		case 21: return "s5";
		case 22: return "s6";
		case 23: return "s7";
		case 24: return "s8";
		case 25: return "s9";
		case 26: return "s10";
		case 27: return "s11";
		case 28: return "t3";
		case 29: return "t4";
		case 30: return "t5";
		case 31: return "t6";
		case 32: return "ft0";
		case 33: return "ft1";
		case 34: return "ft2";
		case 35: return "ft3";
		case 36: return "ft4";
		case 37: return "ft5";
		case 38: return "ft6";
		case 39: return "ft7";
		case 40: return "fs0";
		case 41: return "fs1";
		case 42: return "fa0";
		case 43: return "fa1";
		case 44: return "fa2";
		case 45: return "fa3";
		case 46: return "fa4";
		case 47: return "fa5";
		case 48: return "fa6";
		case 49: return "fa7";
		case 50: return "fs2";
		case 51: return "fs3";
		case 52: return "fs4";
		case 53: return "fs5";
		case 54: return "fs6";
		case 55: return "fs7";
		case 56: return "fs8";
		case 57: return "fs9";
		case 58: return "fs10";
		case 59: return "fs11";
		case 60: return "ft8";
		case 61: return "ft9";
		case 62: return "ft10";
		case 63: return "ft11";
		default: return (NULL);
		}
	case EM_X86_64:
		switch (reg) {
		case 0: return "rax";
		case 1: return "rdx";
		case 2: return "rcx";
		case 3: return "rbx";
		case 4: return "rsi";
		case 5: return "rdi";
		case 6: return "rbp";
		case 7: return "rsp";
		case 16: return "rip";
		case 17: return "xmm0";
		case 18: return "xmm1";
		case 19: return "xmm2";
		case 20: return "xmm3";
		case 21: return "xmm4";
		case 22: return "xmm5";
		case 23: return "xmm6";
		case 24: return "xmm7";
		case 25: return "xmm8";
		case 26: return "xmm9";
		case 27: return "xmm10";
		case 28: return "xmm11";
		case 29: return "xmm12";
		case 30: return "xmm13";
		case 31: return "xmm14";
		case 32: return "xmm15";
		case 33: return "st0";
		case 34: return "st1";
		case 35: return "st2";
		case 36: return "st3";
		case 37: return "st4";
		case 38: return "st5";
		case 39: return "st6";
		case 40: return "st7";
		case 41: return "mm0";
		case 42: return "mm1";
		case 43: return "mm2";
		case 44: return "mm3";
		case 45: return "mm4";
		case 46: return "mm5";
		case 47: return "mm6";
		case 48: return "mm7";
		case 49: return "rflags";
		case 50: return "es";
		case 51: return "cs";
		case 52: return "ss";
		case 53: return "ds";
		case 54: return "fs";
		case 55: return "gs";
		case 58: return "fs.base";
		case 59: return "gs.base";
		case 62: return "tr";
		case 63: return "ldtr";
		case 64: return "mxcsr";
		case 65: return "fcw";
		case 66: return "fsw";
		default: return (NULL);
		}
	default:
		return (NULL);
	}
}