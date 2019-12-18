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
struct bfd_target {int dummy; } ;
typedef  struct bfd_target bfd_target ;
typedef  int bfd_boolean ;

/* Variables and functions */

__attribute__((used)) static bfd_boolean
is_ppc64_elf_target (const struct bfd_target *targ)
{
  extern const bfd_target bfd_elf64_powerpc_vec;
  extern const bfd_target bfd_elf64_powerpcle_vec;

  return targ == &bfd_elf64_powerpc_vec || targ == &bfd_elf64_powerpcle_vec;
}