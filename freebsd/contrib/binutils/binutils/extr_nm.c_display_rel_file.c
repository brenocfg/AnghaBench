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
struct size_sym {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int HAS_SYMS ; 
 int /*<<< orphan*/  _ (char*) ; 
 long bfd_canonicalize_dynamic_symtab (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 long bfd_get_dynamic_symtab_upper_bound (int /*<<< orphan*/ *) ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 long bfd_get_synthetic_symtab (int /*<<< orphan*/ *,long,int /*<<< orphan*/ **,long,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 void* bfd_make_empty_symbol (int /*<<< orphan*/ *) ; 
 long bfd_read_minisymbols (int /*<<< orphan*/ *,scalar_t__,void**,unsigned int*) ; 
 scalar_t__ dynamic ; 
 long filter_symbols (int /*<<< orphan*/ *,scalar_t__,void*,long,unsigned int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,void*,long) ; 
 int /*<<< orphan*/  no_sort ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_size_symbols (int /*<<< orphan*/ *,scalar_t__,struct size_sym*,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_symbols (int /*<<< orphan*/ *,scalar_t__,void*,long,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qsort (void*,long,unsigned int,int /*<<< orphan*/ ) ; 
 size_t reverse_sort ; 
 scalar_t__ show_synthetic ; 
 int /*<<< orphan*/ * sort_bfd ; 
 int /*<<< orphan*/  sort_by_size ; 
 scalar_t__ sort_dynamic ; 
 size_t sort_numerically ; 
 long sort_symbols_by_size (int /*<<< orphan*/ *,scalar_t__,void*,long,unsigned int,struct size_sym**) ; 
 int /*<<< orphan*/ * sort_x ; 
 int /*<<< orphan*/ * sort_y ; 
 int /*<<< orphan*/ ** sorters ; 
 void* xmalloc (long) ; 

__attribute__((used)) static void
display_rel_file (bfd *abfd, bfd *archive_bfd)
{
  long symcount;
  void *minisyms;
  unsigned int size;
  struct size_sym *symsizes;

  if (! dynamic)
    {
      if (!(bfd_get_file_flags (abfd) & HAS_SYMS))
	{
	  non_fatal (_("%s: no symbols"), bfd_get_filename (abfd));
	  return;
	}
    }

  symcount = bfd_read_minisymbols (abfd, dynamic, &minisyms, &size);
  if (symcount < 0)
    bfd_fatal (bfd_get_filename (abfd));

  if (symcount == 0)
    {
      non_fatal (_("%s: no symbols"), bfd_get_filename (abfd));
      return;
    }

  if (show_synthetic && size == sizeof (asymbol *))
    {
      asymbol *synthsyms;
      long synth_count;
      asymbol **static_syms = NULL;
      asymbol **dyn_syms = NULL;
      long static_count = 0;
      long dyn_count = 0;

      if (dynamic)
	{
	  dyn_count = symcount;
	  dyn_syms = minisyms;
	}
      else
	{
	  long storage = bfd_get_dynamic_symtab_upper_bound (abfd);

	  static_count = symcount;
	  static_syms = minisyms;

	  if (storage > 0)
	    {
	      dyn_syms = xmalloc (storage);
	      dyn_count = bfd_canonicalize_dynamic_symtab (abfd, dyn_syms);
	      if (dyn_count < 0)
		bfd_fatal (bfd_get_filename (abfd));
	    }
	}
      synth_count = bfd_get_synthetic_symtab (abfd, static_count, static_syms,
					      dyn_count, dyn_syms, &synthsyms);
      if (synth_count > 0)
	{
	  asymbol **symp;
	  void *new_mini;
	  long i;

	  new_mini = xmalloc ((symcount + synth_count + 1) * sizeof (*symp));
	  symp = new_mini;
	  memcpy (symp, minisyms, symcount * sizeof (*symp));
	  symp += symcount;
	  for (i = 0; i < synth_count; i++)
	    *symp++ = synthsyms + i;
	  *symp = 0;
	  minisyms = new_mini;
	  symcount += synth_count;
	}
    }

  /* Discard the symbols we don't want to print.
     It's OK to do this in place; we'll free the storage anyway
     (after printing).  */

  symcount = filter_symbols (abfd, dynamic, minisyms, symcount, size);

  symsizes = NULL;
  if (! no_sort)
    {
      sort_bfd = abfd;
      sort_dynamic = dynamic;
      sort_x = bfd_make_empty_symbol (abfd);
      sort_y = bfd_make_empty_symbol (abfd);
      if (sort_x == NULL || sort_y == NULL)
	bfd_fatal (bfd_get_filename (abfd));

      if (! sort_by_size)
	qsort (minisyms, symcount, size,
	       sorters[sort_numerically][reverse_sort]);
      else
	symcount = sort_symbols_by_size (abfd, dynamic, minisyms, symcount,
					 size, &symsizes);
    }

  if (! sort_by_size)
    print_symbols (abfd, dynamic, minisyms, symcount, size, archive_bfd);
  else
    print_size_symbols (abfd, dynamic, symsizes, symcount, archive_bfd);

  free (minisyms);
}