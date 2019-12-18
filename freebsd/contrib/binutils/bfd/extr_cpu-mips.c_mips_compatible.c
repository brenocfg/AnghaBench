#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ arch; } ;
typedef  TYPE_1__ bfd_arch_info_type ;

/* Variables and functions */

__attribute__((used)) static const bfd_arch_info_type *
mips_compatible (const bfd_arch_info_type *a, const bfd_arch_info_type *b)
{
  if (a->arch != b->arch)
    return NULL;

  /* Machine compatibility is checked in
     _bfd_mips_elf_merge_private_bfd_data.  */

  return a;
}