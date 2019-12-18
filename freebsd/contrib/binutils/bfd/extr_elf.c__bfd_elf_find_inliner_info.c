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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  dwarf2_find_line_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_dwarf2_find_inliner_info (int /*<<< orphan*/ *,char const**,char const**,unsigned int*,int /*<<< orphan*/ *) ; 
 TYPE_1__* elf_tdata (int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_elf_find_inliner_info (bfd *abfd,
			    const char **filename_ptr,
			    const char **functionname_ptr,
			    unsigned int *line_ptr)
{
  bfd_boolean found;
  found = _bfd_dwarf2_find_inliner_info (abfd, filename_ptr,
					 functionname_ptr, line_ptr,
					 & elf_tdata (abfd)->dwarf2_find_line_info);
  return found;
}