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
typedef  int /*<<< orphan*/  reloc_howto_type ;

/* Variables and functions */
#define  R_SPARC_GNU_VTENTRY 130 
#define  R_SPARC_GNU_VTINHERIT 129 
 unsigned int R_SPARC_NONE ; 
#define  R_SPARC_REV32 128 
 scalar_t__ R_SPARC_max_std ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * _bfd_sparc_elf_howto_table ; 
 int /*<<< orphan*/  sparc_rev32_howto ; 
 int /*<<< orphan*/  sparc_vtentry_howto ; 
 int /*<<< orphan*/  sparc_vtinherit_howto ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

reloc_howto_type *
_bfd_sparc_elf_info_to_howto_ptr (unsigned int r_type)
{
  switch (r_type)
    {
    case R_SPARC_GNU_VTINHERIT:
      return &sparc_vtinherit_howto;

    case R_SPARC_GNU_VTENTRY:
      return &sparc_vtentry_howto;

    case R_SPARC_REV32:
      return &sparc_rev32_howto;

    default:
      if (r_type >= (unsigned int) R_SPARC_max_std)
	{
	  (*_bfd_error_handler) (_("invalid relocation type %d"),
				 (int) r_type);
	  r_type = R_SPARC_NONE;
	}
      return &_bfd_sparc_elf_howto_table[r_type];
    }
}