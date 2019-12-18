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
typedef  int bfd_vma ;

/* Variables and functions */
 int ELF32_R_SYM (int) ; 

__attribute__((used)) static bfd_vma
sparc_elf_r_symndx_64 (bfd_vma r_info)
{
  bfd_vma r_symndx = ELF32_R_SYM (r_info);
  return (r_symndx >> 24);
}