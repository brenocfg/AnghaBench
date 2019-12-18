#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int flags; TYPE_4__* section; } ;
typedef  TYPE_2__ asymbol ;
struct TYPE_7__ {TYPE_1__* output_section; } ;
struct TYPE_5__ {scalar_t__ vma; } ;

/* Variables and functions */
 int BSF_SECTION_SYM ; 
 scalar_t__ _ (char*) ; 
 scalar_t__ _bfd_get_gp_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_set_gp_value (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ bfd_is_und_section (TYPE_4__*) ; 
 int /*<<< orphan*/  bfd_reloc_dangerous ; 
 int /*<<< orphan*/  bfd_reloc_ok ; 
 int /*<<< orphan*/  bfd_reloc_undefined ; 
 int /*<<< orphan*/  mips_elf64_assign_gp (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bfd_reloc_status_type
mips_elf64_final_gp (bfd *output_bfd, asymbol *symbol, bfd_boolean relocatable,
		     char **error_message, bfd_vma *pgp)
{
  if (bfd_is_und_section (symbol->section)
      && ! relocatable)
    {
      *pgp = 0;
      return bfd_reloc_undefined;
    }

  *pgp = _bfd_get_gp_value (output_bfd);
  if (*pgp == 0
      && (! relocatable
	  || (symbol->flags & BSF_SECTION_SYM) != 0))
    {
      if (relocatable)
	{
	  /* Make up a value.  */
	  *pgp = symbol->section->output_section->vma /*+ 0x4000*/;
	  _bfd_set_gp_value (output_bfd, *pgp);
	}
      else if (!mips_elf64_assign_gp (output_bfd, pgp))
	{
	  *error_message =
	    (char *) _("GP relative relocation when _gp not defined");
	  return bfd_reloc_dangerous;
	}
    }

  return bfd_reloc_ok;
}