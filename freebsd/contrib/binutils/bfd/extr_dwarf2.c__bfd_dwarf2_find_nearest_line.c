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
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  find_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const**,char const**,unsigned int*,unsigned int,void**) ; 

bfd_boolean
_bfd_dwarf2_find_nearest_line (bfd *abfd,
			       asection *section,
			       asymbol **symbols,
			       bfd_vma offset,
			       const char **filename_ptr,
			       const char **functionname_ptr,
			       unsigned int *linenumber_ptr,
			       unsigned int addr_size,
			       void **pinfo)
{
  return find_line (abfd, section, offset, NULL, symbols, filename_ptr,
		    functionname_ptr, linenumber_ptr, addr_size,
		    pinfo);
}