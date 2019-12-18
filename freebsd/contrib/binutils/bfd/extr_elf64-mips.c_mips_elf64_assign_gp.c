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
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int _bfd_get_gp_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_set_gp_value (int /*<<< orphan*/ *,int) ; 
 char* bfd_asymbol_name (int /*<<< orphan*/ *) ; 
 int bfd_asymbol_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** bfd_get_outsymbols (int /*<<< orphan*/ *) ; 
 unsigned int bfd_get_symcount (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bfd_boolean
mips_elf64_assign_gp (bfd *output_bfd, bfd_vma *pgp)
{
  unsigned int count;
  asymbol **sym;
  unsigned int i;

  /* If we've already figured out what GP will be, just return it.  */
  *pgp = _bfd_get_gp_value (output_bfd);
  if (*pgp)
    return TRUE;

  count = bfd_get_symcount (output_bfd);
  sym = bfd_get_outsymbols (output_bfd);

  /* The linker script will have created a symbol named `_gp' with the
     appropriate value.  */
  if (sym == NULL)
    i = count;
  else
    {
      for (i = 0; i < count; i++, sym++)
	{
	  register const char *name;

	  name = bfd_asymbol_name (*sym);
	  if (*name == '_' && strcmp (name, "_gp") == 0)
	    {
	      *pgp = bfd_asymbol_value (*sym);
	      _bfd_set_gp_value (output_bfd, *pgp);
	      break;
	    }
	}
    }

  if (i >= count)
    {
      /* Only get the error once.  */
      *pgp = 4;
      _bfd_set_gp_value (output_bfd, *pgp);
      return FALSE;
    }

  return TRUE;
}