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
struct TYPE_2__ {int ld_symb_size; scalar_t__ ld_symbols; scalar_t__ ld_stab; } ;
struct sunos_dynamic_info {scalar_t__ dynsym_count; int /*<<< orphan*/ * dynstr; TYPE_1__ dyninfo; int /*<<< orphan*/ * dynsym; int /*<<< orphan*/  valid; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int EXTERNAL_NLIST_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 void* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 int bfd_bread (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_no_symbols ; 
 int /*<<< orphan*/  bfd_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obj_aout_dynamic_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunos_read_dynamic_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
sunos_slurp_dynamic_symtab (bfd *abfd)
{
  struct sunos_dynamic_info *info;
  bfd_size_type amt;

  /* Get the general dynamic information.  */
  if (obj_aout_dynamic_info (abfd) == NULL)
    {
      if (! sunos_read_dynamic_info (abfd))
	  return FALSE;
    }

  info = (struct sunos_dynamic_info *) obj_aout_dynamic_info (abfd);
  if (! info->valid)
    {
      bfd_set_error (bfd_error_no_symbols);
      return FALSE;
    }

  /* Get the dynamic nlist structures.  */
  if (info->dynsym == NULL)
    {
      amt = (bfd_size_type) info->dynsym_count * EXTERNAL_NLIST_SIZE;
      info->dynsym = bfd_alloc (abfd, amt);
      if (info->dynsym == NULL && info->dynsym_count != 0)
	return FALSE;
      if (bfd_seek (abfd, (file_ptr) info->dyninfo.ld_stab, SEEK_SET) != 0
	  || bfd_bread ((void *) info->dynsym, amt, abfd) != amt)
	{
	  if (info->dynsym != NULL)
	    {
	      bfd_release (abfd, info->dynsym);
	      info->dynsym = NULL;
	    }
	  return FALSE;
	}
    }

  /* Get the dynamic strings.  */
  if (info->dynstr == NULL)
    {
      amt = info->dyninfo.ld_symb_size;
      info->dynstr = bfd_alloc (abfd, amt);
      if (info->dynstr == NULL && info->dyninfo.ld_symb_size != 0)
	return FALSE;
      if (bfd_seek (abfd, (file_ptr) info->dyninfo.ld_symbols, SEEK_SET) != 0
	  || bfd_bread ((void *) info->dynstr, amt, abfd) != amt)
	{
	  if (info->dynstr != NULL)
	    {
	      bfd_release (abfd, info->dynstr);
	      info->dynstr = NULL;
	    }
	  return FALSE;
	}
    }

  return TRUE;
}