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
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 long bfd_canonicalize_dynamic_symtab (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 long bfd_canonicalize_symtab (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bfd_error_no_symbols ; 
 long bfd_get_dynamic_symtab_upper_bound (int /*<<< orphan*/ *) ; 
 long bfd_get_symtab_upper_bound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** bfd_malloc (long) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 

long
_bfd_generic_read_minisymbols (bfd *abfd,
			       bfd_boolean dynamic,
			       void **minisymsp,
			       unsigned int *sizep)
{
  long storage;
  asymbol **syms = NULL;
  long symcount;

  if (dynamic)
    storage = bfd_get_dynamic_symtab_upper_bound (abfd);
  else
    storage = bfd_get_symtab_upper_bound (abfd);
  if (storage < 0)
    goto error_return;
  if (storage == 0)
    return 0;

  syms = bfd_malloc (storage);
  if (syms == NULL)
    goto error_return;

  if (dynamic)
    symcount = bfd_canonicalize_dynamic_symtab (abfd, syms);
  else
    symcount = bfd_canonicalize_symtab (abfd, syms);
  if (symcount < 0)
    goto error_return;

  *minisymsp = syms;
  *sizep = sizeof (asymbol *);
  return symcount;

 error_return:
  bfd_set_error (bfd_error_no_symbols);
  if (syms != NULL)
    free (syms);
  return -1;
}