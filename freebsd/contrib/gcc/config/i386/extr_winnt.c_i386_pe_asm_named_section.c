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
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 unsigned int SECTION_CODE ; 
 unsigned int SECTION_LINKONCE ; 
 unsigned int SECTION_PE_SHARED ; 
 unsigned int SECTION_WRITE ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 

void
i386_pe_asm_named_section (const char *name, unsigned int flags, 
			   tree decl)
{
  char flagchars[8], *f = flagchars;

  if ((flags & (SECTION_CODE | SECTION_WRITE)) == 0)
    /* readonly data */
    {
      *f++ ='d';  /* This is necessary for older versions of gas.  */
      *f++ ='r';
    }
  else	
    {
      if (flags & SECTION_CODE)
        *f++ = 'x';
      if (flags & SECTION_WRITE)
        *f++ = 'w';
      if (flags & SECTION_PE_SHARED)
        *f++ = 's';
    }

  *f = '\0';

  fprintf (asm_out_file, "\t.section\t%s,\"%s\"\n", name, flagchars);

  if (flags & SECTION_LINKONCE)
    {
      /* Functions may have been compiled at various levels of
	 optimization so we can't use `same_size' here.
	 Instead, have the linker pick one, without warning.
	 If 'selectany' attribute has been specified,  MS compiler
	 sets 'discard' characteristic, rather than telling linker
	 to warn of size or content mismatch, so do the same.  */ 
      bool discard = (flags & SECTION_CODE)
		      || lookup_attribute ("selectany",
					   DECL_ATTRIBUTES (decl));	 
      fprintf (asm_out_file, "\t.linkonce %s\n",
	       (discard  ? "discard" : "same_size"));
    }
}