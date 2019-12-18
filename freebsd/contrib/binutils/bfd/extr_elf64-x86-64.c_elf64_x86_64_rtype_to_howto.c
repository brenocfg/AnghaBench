#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int type; } ;
typedef  TYPE_1__ reloc_howto_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ R_X86_64_GNU_VTINHERIT ; 
 unsigned int R_X86_64_NONE ; 
 scalar_t__ R_X86_64_max ; 
 scalar_t__ R_X86_64_standard ; 
 scalar_t__ R_X86_64_vt_offset ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* x86_64_elf_howto_table ; 

__attribute__((used)) static reloc_howto_type *
elf64_x86_64_rtype_to_howto (bfd *abfd, unsigned r_type)
{
  unsigned i;

  if (r_type < (unsigned int) R_X86_64_GNU_VTINHERIT
      || r_type >= (unsigned int) R_X86_64_max)
    {
      if (r_type >= (unsigned int) R_X86_64_standard)
	{
	  (*_bfd_error_handler) (_("%B: invalid relocation type %d"),
				 abfd, (int) r_type);
	  r_type = R_X86_64_NONE;
	}
      i = r_type;
    }
  else
    i = r_type - (unsigned int) R_X86_64_vt_offset;
  BFD_ASSERT (x86_64_elf_howto_table[i].type == r_type);
  return &x86_64_elf_howto_table[i];
}