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
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_2__ {scalar_t__ versioned_name; } ;

/* Variables and functions */
 char ELF_VER_CHR ; 
 int /*<<< orphan*/  S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_WEAK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  know (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 char* strchr (scalar_t__,char) ; 
 int strlen (char*) ; 
 TYPE_1__* symbol_get_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_lastP ; 
 int /*<<< orphan*/ * symbol_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_rootP ; 
 scalar_t__ symbol_used_in_reloc_p (int /*<<< orphan*/ *) ; 
 scalar_t__ symbol_used_p (int /*<<< orphan*/ *) ; 

void
elf_frob_file_before_adjust (void)
{
  if (symbol_rootP)
    {
      symbolS *symp;

      for (symp = symbol_rootP; symp; symp = symbol_next (symp))
	if (!S_IS_DEFINED (symp))
	  {
	    if (symbol_get_obj (symp)->versioned_name)
	      {
		char *p;

		/* The @@@ syntax is a special case. If the symbol is
		   not defined, 2 `@'s will be removed from the
		   versioned_name.  */

		p = strchr (symbol_get_obj (symp)->versioned_name,
			    ELF_VER_CHR);
		know (p != NULL);
		if (p[1] == ELF_VER_CHR && p[2] == ELF_VER_CHR)
		  {
		    size_t l = strlen (&p[3]) + 1;
		    memmove (&p[1], &p[3], l);
		  }
		if (symbol_used_p (symp) == 0
		    && symbol_used_in_reloc_p (symp) == 0)
		  symbol_remove (symp, &symbol_rootP, &symbol_lastP);
	      }

	    /* If there was .weak foo, but foo was neither defined nor
	       used anywhere, remove it.  */

	    else if (S_IS_WEAK (symp)
		     && symbol_used_p (symp) == 0
		     && symbol_used_in_reloc_p (symp) == 0)
	      symbol_remove (symp, &symbol_rootP, &symbol_lastP);
	  }
    }
}