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
 unsigned int ARRAY_SIZE (char const* const*) ; 
 scalar_t__ CODE_64BIT ; 
 scalar_t__ flag_code ; 
 scalar_t__ strcmp (char*,char const* const) ; 

int
tc_x86_regname_to_dw2regnum (char *regname)
{
  unsigned int regnum;
  unsigned int regnames_count;
  static const char *const regnames_32[] =
    {
      "eax", "ecx", "edx", "ebx",
      "esp", "ebp", "esi", "edi",
      "eip", "eflags", NULL,
      "st0", "st1", "st2", "st3",
      "st4", "st5", "st6", "st7",
      NULL, NULL,
      "xmm0", "xmm1", "xmm2", "xmm3",
      "xmm4", "xmm5", "xmm6", "xmm7",
      "mm0", "mm1", "mm2", "mm3",
      "mm4", "mm5", "mm6", "mm7",
      "fcw", "fsw", "mxcsr",
      "es", "cs", "ss", "ds", "fs", "gs", NULL, NULL,
      "tr", "ldtr"
    };
  static const char *const regnames_64[] =
    {
      "rax", "rdx", "rcx", "rbx",
      "rsi", "rdi", "rbp", "rsp",
      "r8",  "r9",  "r10", "r11",
      "r12", "r13", "r14", "r15",
      "rip",
      "xmm0",  "xmm1",  "xmm2",  "xmm3",
      "xmm4",  "xmm5",  "xmm6",  "xmm7",
      "xmm8",  "xmm9",  "xmm10", "xmm11",
      "xmm12", "xmm13", "xmm14", "xmm15",
      "st0", "st1", "st2", "st3",
      "st4", "st5", "st6", "st7",
      "mm0", "mm1", "mm2", "mm3",
      "mm4", "mm5", "mm6", "mm7",
      "rflags",
      "es", "cs", "ss", "ds", "fs", "gs", NULL, NULL,
      "fs.base", "gs.base", NULL, NULL,
      "tr", "ldtr",
      "mxcsr", "fcw", "fsw"
    };
  const char *const *regnames;

  if (flag_code == CODE_64BIT)
    {
      regnames = regnames_64;
      regnames_count = ARRAY_SIZE (regnames_64);
    }
  else
    {
      regnames = regnames_32;
      regnames_count = ARRAY_SIZE (regnames_32);
    }

  for (regnum = 0; regnum < regnames_count; regnum++)
    if (regnames[regnum] != NULL
	&& strcmp (regname, regnames[regnum]) == 0)
      return regnum;

  return -1;
}