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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 unsigned int SECTION_CODE ; 
 unsigned int SECTION_LINKONCE ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  default_coff_asm_named_section (char const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 

void
default_pe_asm_named_section (const char *name, unsigned int flags,
			      tree decl)
{
  default_coff_asm_named_section (name, flags, decl);

  if (flags & SECTION_LINKONCE)
    {
      /* Functions may have been compiled at various levels of
         optimization so we can't use `same_size' here.
         Instead, have the linker pick one.  */
      fprintf (asm_out_file, "\t.linkonce %s\n",
	       (flags & SECTION_CODE ? "discard" : "same_size"));
    }
}