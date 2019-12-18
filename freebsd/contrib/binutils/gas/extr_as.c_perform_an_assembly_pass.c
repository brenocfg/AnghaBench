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
typedef  int flagword ;
struct TYPE_2__ {int bss; } ;

/* Variables and functions */
 char* BFD_ABS_SECTION_NAME ; 
 char* BFD_UND_SECTION_NAME ; 
 char* BSS_SECTION_NAME ; 
 char* DATA_SECTION_NAME ; 
 int /*<<< orphan*/  PROGRESS (int) ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_DATA ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int SEC_RELOC ; 
 char* TEXT_SECTION_NAME ; 
 int bfd_applicable_section_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,void*,int) ; 
 void* bss_section ; 
 void* data_section ; 
 void* expr_section ; 
 int /*<<< orphan*/  gas_cgen_begin () ; 
 int /*<<< orphan*/  md_begin () ; 
 scalar_t__ need_pass_2 ; 
 int /*<<< orphan*/  obj_begin () ; 
 int /*<<< orphan*/  read_a_source_file (char*) ; 
 void* reg_section ; 
 TYPE_1__* seg_info (void*) ; 
 int /*<<< orphan*/  stdoutput ; 
 void* subseg_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subseg_set (void*,int /*<<< orphan*/ ) ; 
 void* text_section ; 

__attribute__((used)) static void
perform_an_assembly_pass (int argc, char ** argv)
{
  int saw_a_file = 0;
  flagword applicable;

  need_pass_2 = 0;

  /* Create the standard sections, and those the assembler uses
     internally.  */
  text_section = subseg_new (TEXT_SECTION_NAME, 0);
  data_section = subseg_new (DATA_SECTION_NAME, 0);
  bss_section = subseg_new (BSS_SECTION_NAME, 0);
  /* @@ FIXME -- we're setting the RELOC flag so that sections are assumed
     to have relocs, otherwise we don't find out in time.  */
  applicable = bfd_applicable_section_flags (stdoutput);
  bfd_set_section_flags (stdoutput, text_section,
			 applicable & (SEC_ALLOC | SEC_LOAD | SEC_RELOC
				       | SEC_CODE | SEC_READONLY));
  bfd_set_section_flags (stdoutput, data_section,
			 applicable & (SEC_ALLOC | SEC_LOAD | SEC_RELOC
				       | SEC_DATA));
  bfd_set_section_flags (stdoutput, bss_section, applicable & SEC_ALLOC);
  seg_info (bss_section)->bss = 1;
  subseg_new (BFD_ABS_SECTION_NAME, 0);
  subseg_new (BFD_UND_SECTION_NAME, 0);
  reg_section = subseg_new ("*GAS `reg' section*", 0);
  expr_section = subseg_new ("*GAS `expr' section*", 0);

  subseg_set (text_section, 0);

  /* This may add symbol table entries, which requires having an open BFD,
     and sections already created.  */
  md_begin ();

#ifdef USING_CGEN
  gas_cgen_begin ();
#endif
#ifdef obj_begin
  obj_begin ();
#endif

  /* Skip argv[0].  */
  argv++;
  argc--;

  while (argc--)
    {
      if (*argv)
	{			/* Is it a file-name argument?  */
	  PROGRESS (1);
	  saw_a_file++;
	  /* argv->"" if stdin desired, else->filename.  */
	  read_a_source_file (*argv);
	}
      argv++;			/* Completed that argv.  */
    }
  if (!saw_a_file)
    read_a_source_file ("");
}