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
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {int /*<<< orphan*/ * X_add_symbol; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ OUTPUT_FLAVOR ; 
 int SEC_LINK_ONCE ; 
 int /*<<< orphan*/ * S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_EXTERNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_LOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_WEAK (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  bfd_abs_section ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_is_com_section (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 int /*<<< orphan*/  bfd_und_section ; 
 int /*<<< orphan*/  segment_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ symbol_equated_reloc_p (int /*<<< orphan*/ *) ; 
 TYPE_1__* symbol_get_value_expression (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
pic_need_relax (symbolS *sym, asection *segtype)
{
  asection *symsec;
  bfd_boolean linkonce;

  /* Handle the case of a symbol equated to another symbol.  */
  while (symbol_equated_reloc_p (sym))
    {
      symbolS *n;

      /* It's possible to get a loop here in a badly written
	 program.  */
      n = symbol_get_value_expression (sym)->X_add_symbol;
      if (n == sym)
	break;
      sym = n;
    }

  symsec = S_GET_SEGMENT (sym);

  /* duplicate the test for LINK_ONCE sections as in adjust_reloc_syms */
  linkonce = FALSE;
  if (symsec != segtype && ! S_IS_LOCAL (sym))
    {
      if ((bfd_get_section_flags (stdoutput, symsec) & SEC_LINK_ONCE) != 0)
	linkonce = TRUE;

      /* The GNU toolchain uses an extension for ELF: a section
	  beginning with the magic string .gnu.linkonce is a linkonce
	  section.  */
      if (strncmp (segment_name (symsec), ".gnu.linkonce",
		   sizeof ".gnu.linkonce" - 1) == 0)
	linkonce = TRUE;
    }

  /* This must duplicate the test in adjust_reloc_syms.  */
  return (symsec != &bfd_und_section
	    && symsec != &bfd_abs_section
	  && ! bfd_is_com_section (symsec)
	    && !linkonce
#ifdef OBJ_ELF
	  /* A global or weak symbol is treated as external.  */
	  && (OUTPUT_FLAVOR != bfd_target_elf_flavour
	      || (! S_IS_WEAK (sym) && ! S_IS_EXTERNAL (sym)))
#endif
	  );
}