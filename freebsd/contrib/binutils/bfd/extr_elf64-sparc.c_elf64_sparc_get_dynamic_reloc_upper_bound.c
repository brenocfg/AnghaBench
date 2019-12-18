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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int _bfd_elf_get_dynamic_reloc_upper_bound (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
elf64_sparc_get_dynamic_reloc_upper_bound (bfd *abfd)
{
  return _bfd_elf_get_dynamic_reloc_upper_bound (abfd) * 2;
}