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
 scalar_t__ ABI_AIX ; 
 scalar_t__ ABI_DARWIN ; 
 scalar_t__ ABI_V4 ; 
 scalar_t__ DEFAULT_ABI ; 
 int FIRST_ALTIVEC_REGNO ; 
 size_t FIXED_SCRATCH ; 
 scalar_t__ INVALID_REGNUM ; 
 int LAST_ALTIVEC_REGNO ; 
 scalar_t__ PIC_OFFSET_TABLE_REGNUM ; 
 size_t RS6000_PIC_OFFSET_TABLE_REGNUM ; 
 size_t SPEFSCR_REGNO ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_ALTIVEC ; 
 scalar_t__ TARGET_ALTIVEC_ABI ; 
 int /*<<< orphan*/  TARGET_FPRS ; 
 scalar_t__ TARGET_MINIMAL_TOC ; 
 int /*<<< orphan*/  TARGET_POWER ; 
 scalar_t__ TARGET_SOFT_FLOAT ; 
 scalar_t__ TARGET_SPE ; 
 scalar_t__ TARGET_TOC ; 
 size_t VRSAVE_REGNO ; 
 size_t VSCR_REGNO ; 
 int* call_really_used_regs ; 
 int* call_used_regs ; 
 int* fixed_regs ; 
 int flag_pic ; 
 int* global_regs ; 

void
rs6000_conditional_register_usage (void)
{
  int i;

  /* Set MQ register fixed (already call_used) if not POWER
     architecture (RIOS1, RIOS2, RSC, and PPC601) so that it will not
     be allocated.  */
  if (! TARGET_POWER)
    fixed_regs[64] = 1;

  /* 64-bit AIX and Linux reserve GPR13 for thread-private data.  */
  if (TARGET_64BIT)
    fixed_regs[13] = call_used_regs[13]
      = call_really_used_regs[13] = 1;

  /* Conditionally disable FPRs.  */
  if (TARGET_SOFT_FLOAT || !TARGET_FPRS)
    for (i = 32; i < 64; i++)
      fixed_regs[i] = call_used_regs[i]
	= call_really_used_regs[i] = 1;

  /* The TOC register is not killed across calls in a way that is
     visible to the compiler.  */
  if (DEFAULT_ABI == ABI_AIX)
    call_really_used_regs[2] = 0;

  if (DEFAULT_ABI == ABI_V4
      && PIC_OFFSET_TABLE_REGNUM != INVALID_REGNUM
      && flag_pic == 2)
    fixed_regs[RS6000_PIC_OFFSET_TABLE_REGNUM] = 1;

  if (DEFAULT_ABI == ABI_V4
      && PIC_OFFSET_TABLE_REGNUM != INVALID_REGNUM
      && flag_pic == 1)
    fixed_regs[RS6000_PIC_OFFSET_TABLE_REGNUM]
      = call_used_regs[RS6000_PIC_OFFSET_TABLE_REGNUM]
      = call_really_used_regs[RS6000_PIC_OFFSET_TABLE_REGNUM] = 1;

  if (DEFAULT_ABI == ABI_DARWIN
      && PIC_OFFSET_TABLE_REGNUM != INVALID_REGNUM)
      fixed_regs[RS6000_PIC_OFFSET_TABLE_REGNUM]
      = call_used_regs[RS6000_PIC_OFFSET_TABLE_REGNUM]
      = call_really_used_regs[RS6000_PIC_OFFSET_TABLE_REGNUM] = 1;

  if (TARGET_TOC && TARGET_MINIMAL_TOC)
    fixed_regs[RS6000_PIC_OFFSET_TABLE_REGNUM]
      = call_used_regs[RS6000_PIC_OFFSET_TABLE_REGNUM] = 1;

  if (TARGET_ALTIVEC)
    global_regs[VSCR_REGNO] = 1;

  if (TARGET_SPE)
    {
      global_regs[SPEFSCR_REGNO] = 1;
      fixed_regs[FIXED_SCRATCH]
	= call_used_regs[FIXED_SCRATCH]
	= call_really_used_regs[FIXED_SCRATCH] = 1;
    }

  if (! TARGET_ALTIVEC)
    {
      for (i = FIRST_ALTIVEC_REGNO; i <= LAST_ALTIVEC_REGNO; ++i)
	fixed_regs[i] = call_used_regs[i] = call_really_used_regs[i] = 1;
      call_really_used_regs[VRSAVE_REGNO] = 1;
    }

  if (TARGET_ALTIVEC_ABI)
    for (i = FIRST_ALTIVEC_REGNO; i < FIRST_ALTIVEC_REGNO + 20; ++i)
      call_used_regs[i] = call_really_used_regs[i] = 1;
}