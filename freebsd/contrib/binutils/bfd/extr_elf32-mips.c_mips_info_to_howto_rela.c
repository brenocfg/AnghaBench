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
typedef  int /*<<< orphan*/  arelent ;
typedef  int /*<<< orphan*/  Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  mips_info_to_howto_rel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mips_info_to_howto_rela (bfd *abfd, arelent *cache_ptr, Elf_Internal_Rela *dst)
{
  mips_info_to_howto_rel (abfd, cache_ptr, dst);

  /* If we ever need to do any extra processing with dst->r_addend
     (the field omitted in an Elf_Internal_Rel) we can do it here.  */
}