#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ static_chain_decl; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int) ; 
 scalar_t__ NO_PROFILE_COUNTERS ; 
 int STATIC_CHAIN_REGNUM ; 
 scalar_t__ TARGET_AUTO_PIC ; 
 scalar_t__ TARGET_GNU_AS ; 
 int /*<<< orphan*/  TARGET_NO_PIC ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* cfun ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

void
ia64_output_function_profiler (FILE *file, int labelno)
{
  bool indirect_call;

  /* If the function needs a static chain and the static chain
     register is r15, we use an indirect call so as to bypass
     the PLT stub in case the executable is dynamically linked,
     because the stub clobbers r15 as per 5.3.6 of the psABI.
     We don't need to do that in non canonical PIC mode.  */

  if (cfun->static_chain_decl && !TARGET_NO_PIC && !TARGET_AUTO_PIC)
    {
      gcc_assert (STATIC_CHAIN_REGNUM == 15);
      indirect_call = true;
    }
  else
    indirect_call = false;

  if (TARGET_GNU_AS)
    fputs ("\t.prologue 4, r40\n", file);
  else
    fputs ("\t.prologue\n\t.save ar.pfs, r40\n", file);
  fputs ("\talloc out0 = ar.pfs, 8, 0, 4, 0\n", file);

  if (NO_PROFILE_COUNTERS)
    fputs ("\tmov out3 = r0\n", file);
  else
    {
      char buf[20];
      ASM_GENERATE_INTERNAL_LABEL (buf, "LP", labelno);

      if (TARGET_AUTO_PIC)
	fputs ("\tmovl out3 = @gprel(", file);
      else
	fputs ("\taddl out3 = @ltoff(", file);
      assemble_name (file, buf);
      if (TARGET_AUTO_PIC)
	fputs (")\n", file);
      else
	fputs ("), r1\n", file);
    }

  if (indirect_call)
    fputs ("\taddl r14 = @ltoff(@fptr(_mcount)), r1\n", file);
  fputs ("\t;;\n", file);

  fputs ("\t.save rp, r42\n", file);
  fputs ("\tmov out2 = b0\n", file);
  if (indirect_call)
    fputs ("\tld8 r14 = [r14]\n\t;;\n", file);
  fputs ("\t.body\n", file);
  fputs ("\tmov out1 = r1\n", file);
  if (indirect_call)
    {
      fputs ("\tld8 r16 = [r14], 8\n\t;;\n", file);
      fputs ("\tmov b6 = r16\n", file);
      fputs ("\tld8 r1 = [r14]\n", file);
      fputs ("\tbr.call.sptk.many b0 = b6\n\t;;\n", file);
    }
  else
    fputs ("\tbr.call.sptk.many b0 = _mcount\n\t;;\n", file);
}