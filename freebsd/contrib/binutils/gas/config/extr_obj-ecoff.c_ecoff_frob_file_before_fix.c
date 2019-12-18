#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
struct TYPE_13__ {int /*<<< orphan*/  name; struct TYPE_13__* next; } ;
typedef  TYPE_1__ asection ;
struct TYPE_14__ {TYPE_1__* sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 unsigned long alpha_fprmask ; 
 int /*<<< orphan*/  alpha_frob_ecoff_data () ; 
 int /*<<< orphan*/  alpha_gp_value ; 
 unsigned long alpha_gprmask ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_ecoff_set_gp_value (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_ecoff_set_regmasks (TYPE_2__*,unsigned long,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  bfd_section_list_prepend (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_section_list_remove (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ bfd_section_size (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_set_section_vma (TYPE_2__*,TYPE_1__*,scalar_t__) ; 
 unsigned long* mips_cprmask ; 
 unsigned long mips_gprmask ; 
 int n_names ; 
 TYPE_2__* stdoutput ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const* const) ; 

void
ecoff_frob_file_before_fix (void)
{
  bfd_vma addr;
  asection *sec;

  /* Set the section VMA values.  We force the .sdata and .sbss
     sections to the end to ensure that their VMA addresses are close
     together so that the GP register can address both of them.  We
     put the .bss section after the .sbss section.

     Also, for the Alpha, we must sort the sections, to make sure they
     appear in the output file in the correct order.  (Actually, maybe
     this is a job for BFD.  But the VMAs computed would be out of
     whack if we computed them given our initial, random ordering.
     It's possible that that wouldn't break things; I could do some
     experimenting sometime and find out.

     This output ordering of sections is magic, on the Alpha, at
     least.  The .lita section must come before .lit8 and .lit4,
     otherwise the OSF/1 linker may silently trash the .lit{4,8}
     section contents.  Also, .text must preceed .rdata.  These differ
     from the order described in some parts of the DEC OSF/1 Assembly
     Language Programmer's Guide, but that order doesn't seem to work
     with their linker.

     I don't know if section ordering on the MIPS is important.  */

  static const char *const names[] =
  {
    /* text segment */
    ".text", ".rdata", ".init", ".fini",
    /* data segment */
    ".data", ".lita", ".lit8", ".lit4", ".sdata", ".got",
    /* bss segment */
    ".sbss", ".bss",
  };
#define n_names ((int) (sizeof (names) / sizeof (names[0])))

  /* Sections that match names, order to be straightened out later.  */
  asection *secs[n_names];
  int i;

  addr = 0;
  for (i = 0; i < n_names; i++)
    secs[i] = NULL;

  for (sec = stdoutput->sections; sec != NULL; sec = sec->next)
    {
      for (i = 0; i < n_names; i++)
	if (!strcmp (sec->name, names[i]))
	  {
	    secs[i] = sec;
	    bfd_section_list_remove (stdoutput, sec);
	    break;
	  }
      if (i == n_names)
	{
	  bfd_set_section_vma (stdoutput, sec, addr);
	  addr += bfd_section_size (stdoutput, sec);
	}
    }
  for (i = 0; i < n_names; i++)
    if (secs[i])
      {
	bfd_set_section_vma (stdoutput, secs[i], addr);
	addr += bfd_section_size (stdoutput, secs[i]);
      }
  for (i = n_names - 1; i >= 0; i--)
    if (secs[i])
      bfd_section_list_prepend (stdoutput, secs[i]);

  /* Fill in the register masks.  */
  {
    unsigned long gprmask = 0;
    unsigned long fprmask = 0;
    unsigned long *cprmask = NULL;

#ifdef TC_MIPS
    /* Fill in the MIPS register masks.  It's probably not worth
       setting up a generic interface for this.  */
    gprmask = mips_gprmask;
    cprmask = mips_cprmask;
#endif

#ifdef TC_ALPHA
    alpha_frob_ecoff_data ();

    if (! bfd_ecoff_set_gp_value (stdoutput, alpha_gp_value))
      as_fatal (_("Can't set GP value"));

    gprmask = alpha_gprmask;
    fprmask = alpha_fprmask;
#endif

    if (! bfd_ecoff_set_regmasks (stdoutput, gprmask, fprmask, cprmask))
      as_fatal (_("Can't set register masks"));
  }
}