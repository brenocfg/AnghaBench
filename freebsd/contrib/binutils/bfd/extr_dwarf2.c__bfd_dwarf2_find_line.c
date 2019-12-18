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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  find_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,unsigned int*,unsigned int,void**) ; 

bfd_boolean
_bfd_dwarf2_find_line (bfd *abfd,
		       asymbol **symbols,
		       asymbol *symbol,
		       const char **filename_ptr,
		       unsigned int *linenumber_ptr,
		       unsigned int addr_size,
		       void **pinfo)
{
  return find_line (abfd, NULL, 0, symbol, symbols, filename_ptr,
		    NULL, linenumber_ptr, addr_size,
		    pinfo);
}