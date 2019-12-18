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
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ bfd_canonicalize_dynamic_symtab (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 long bfd_get_dynamic_symtab_upper_bound (int /*<<< orphan*/ *) ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ dynsymcount ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** xmalloc (long) ; 

__attribute__((used)) static asymbol **
slurp_dynamic_symtab (bfd *abfd)
{
  asymbol **sy = NULL;
  long storage;

  storage = bfd_get_dynamic_symtab_upper_bound (abfd);
  if (storage < 0)
    {
      if (!(bfd_get_file_flags (abfd) & DYNAMIC))
	{
	  non_fatal (_("%s: not a dynamic object"), bfd_get_filename (abfd));
	  dynsymcount = 0;
	  return NULL;
	}

      bfd_fatal (bfd_get_filename (abfd));
    }
  if (storage)
    sy = xmalloc (storage);

  dynsymcount = bfd_canonicalize_dynamic_symtab (abfd, sy);
  if (dynsymcount < 0)
    bfd_fatal (bfd_get_filename (abfd));
  return sy;
}