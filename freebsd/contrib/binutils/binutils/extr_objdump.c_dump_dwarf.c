#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int DYNAMIC ; 
 int EXEC_P ; 
 int HAS_RELOC ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_big_endian (TYPE_1__*) ; 
 int bfd_get_arch_size (TYPE_1__*) ; 
 scalar_t__ bfd_little_endian (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_map_over_sections (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  byte_get ; 
 int /*<<< orphan*/  byte_get_big_endian ; 
 int /*<<< orphan*/  byte_get_little_endian ; 
 int /*<<< orphan*/  check_mach_o_dwarf (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_dwarf_section ; 
 int eh_addr_size ; 
 int /*<<< orphan*/  free_debug_memory () ; 
 int is_relocatable ; 

__attribute__((used)) static void
dump_dwarf (bfd *abfd)
{
  is_relocatable = ((abfd->flags & (HAS_RELOC | EXEC_P | DYNAMIC))
		    == HAS_RELOC);

  /* FIXME: bfd_get_arch_size may return -1.  We assume that 64bit
     targets will return 64.  */
  eh_addr_size = bfd_get_arch_size (abfd) == 64 ? 8 : 4;

  if (bfd_big_endian (abfd))
    byte_get = byte_get_big_endian;
  else if (bfd_little_endian (abfd))
    byte_get = byte_get_little_endian;
  else
    abort ();

  check_mach_o_dwarf (abfd);

  bfd_map_over_sections (abfd, dump_dwarf_section, NULL);

  free_debug_memory ();
}