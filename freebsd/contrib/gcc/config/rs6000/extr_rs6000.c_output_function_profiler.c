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
struct TYPE_2__ {int /*<<< orphan*/ * static_chain_decl; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  ABI_AIX 130 
#define  ABI_DARWIN 129 
#define  ABI_V4 128 
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int) ; 
 int DEFAULT_ABI ; 
 int /*<<< orphan*/  NO_PROFILE_COUNTERS ; 
 char* RS6000_MCOUNT ; 
 size_t STATIC_CHAIN_REGNUM ; 
 int /*<<< orphan*/  TARGET_32BIT ; 
 int /*<<< orphan*/  TARGET_PROFILE_KERNEL ; 
 int /*<<< orphan*/  TARGET_SECURE_PLT ; 
 int /*<<< orphan*/  asm_fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* cfun ; 
 int flag_pic ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 char** reg_names ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
output_function_profiler (FILE *file, int labelno)
{
  char buf[100];

  switch (DEFAULT_ABI)
    {
    default:
      gcc_unreachable ();

    case ABI_V4:
      if (!TARGET_32BIT)
	{
	  warning (0, "no profiling of 64-bit code for this ABI");
	  return;
	}
      ASM_GENERATE_INTERNAL_LABEL (buf, "LP", labelno);
      fprintf (file, "\tmflr %s\n", reg_names[0]);
      if (NO_PROFILE_COUNTERS)
	{
	  asm_fprintf (file, "\t{st|stw} %s,4(%s)\n",
		       reg_names[0], reg_names[1]);
	}
      else if (TARGET_SECURE_PLT && flag_pic)
	{
	  asm_fprintf (file, "\tbcl 20,31,1f\n1:\n\t{st|stw} %s,4(%s)\n",
		       reg_names[0], reg_names[1]);
	  asm_fprintf (file, "\tmflr %s\n", reg_names[12]);
	  asm_fprintf (file, "\t{cau|addis} %s,%s,",
		       reg_names[12], reg_names[12]);
	  assemble_name (file, buf);
	  asm_fprintf (file, "-1b@ha\n\t{cal|la} %s,", reg_names[0]);
	  assemble_name (file, buf);
	  asm_fprintf (file, "-1b@l(%s)\n", reg_names[12]);
	}
      else if (flag_pic == 1)
	{
	  fputs ("\tbl _GLOBAL_OFFSET_TABLE_@local-4\n", file);
	  asm_fprintf (file, "\t{st|stw} %s,4(%s)\n",
		       reg_names[0], reg_names[1]);
	  asm_fprintf (file, "\tmflr %s\n", reg_names[12]);
	  asm_fprintf (file, "\t{l|lwz} %s,", reg_names[0]);
	  assemble_name (file, buf);
	  asm_fprintf (file, "@got(%s)\n", reg_names[12]);
	}
      else if (flag_pic > 1)
	{
	  asm_fprintf (file, "\t{st|stw} %s,4(%s)\n",
		       reg_names[0], reg_names[1]);
	  /* Now, we need to get the address of the label.  */
	  fputs ("\tbcl 20,31,1f\n\t.long ", file);
	  assemble_name (file, buf);
	  fputs ("-.\n1:", file);
	  asm_fprintf (file, "\tmflr %s\n", reg_names[11]);
	  asm_fprintf (file, "\t{l|lwz} %s,0(%s)\n",
		       reg_names[0], reg_names[11]);
	  asm_fprintf (file, "\t{cax|add} %s,%s,%s\n",
		       reg_names[0], reg_names[0], reg_names[11]);
	}
      else
	{
	  asm_fprintf (file, "\t{liu|lis} %s,", reg_names[12]);
	  assemble_name (file, buf);
	  fputs ("@ha\n", file);
	  asm_fprintf (file, "\t{st|stw} %s,4(%s)\n",
		       reg_names[0], reg_names[1]);
	  asm_fprintf (file, "\t{cal|la} %s,", reg_names[0]);
	  assemble_name (file, buf);
	  asm_fprintf (file, "@l(%s)\n", reg_names[12]);
	}

      /* ABI_V4 saves the static chain reg with ASM_OUTPUT_REG_PUSH.  */
      fprintf (file, "\tbl %s%s\n",
	       RS6000_MCOUNT, flag_pic ? "@plt" : "");
      break;

    case ABI_AIX:
    case ABI_DARWIN:
      if (!TARGET_PROFILE_KERNEL)
	{
	  /* Don't do anything, done in output_profile_hook ().  */
	}
      else
	{
	  gcc_assert (!TARGET_32BIT);

	  asm_fprintf (file, "\tmflr %s\n", reg_names[0]);
	  asm_fprintf (file, "\tstd %s,16(%s)\n", reg_names[0], reg_names[1]);

	  if (cfun->static_chain_decl != NULL)
	    {
	      asm_fprintf (file, "\tstd %s,24(%s)\n",
			   reg_names[STATIC_CHAIN_REGNUM], reg_names[1]);
	      fprintf (file, "\tbl %s\n", RS6000_MCOUNT);
	      asm_fprintf (file, "\tld %s,24(%s)\n",
			   reg_names[STATIC_CHAIN_REGNUM], reg_names[1]);
	    }
	  else
	    fprintf (file, "\tbl %s\n", RS6000_MCOUNT);
	}
      break;
    }
}