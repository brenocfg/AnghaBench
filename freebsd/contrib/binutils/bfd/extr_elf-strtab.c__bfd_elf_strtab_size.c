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
struct elf_strtab_hash {scalar_t__ size; scalar_t__ sec_size; } ;
typedef  scalar_t__ bfd_size_type ;

/* Variables and functions */

bfd_size_type
_bfd_elf_strtab_size (struct elf_strtab_hash *tab)
{
  return tab->sec_size ? tab->sec_size : tab->size;
}