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
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_2__ {int /*<<< orphan*/  dwarf2_find_line_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_dwarf2_find_line (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const**,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* elf_tdata (int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_elf_find_line (bfd *abfd, asymbol **symbols, asymbol *symbol,
		    const char **filename_ptr, unsigned int *line_ptr)
{
  return _bfd_dwarf2_find_line (abfd, symbols, symbol,
				filename_ptr, line_ptr, 0,
				&elf_tdata (abfd)->dwarf2_find_line_info);
}