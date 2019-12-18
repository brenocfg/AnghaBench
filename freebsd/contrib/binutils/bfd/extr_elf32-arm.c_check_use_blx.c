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
struct elf32_arm_link_hash_table {int use_blx; int /*<<< orphan*/  obfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_ATTR_PROC ; 
 int /*<<< orphan*/  Tag_CPU_arch ; 
 int bfd_elf_get_obj_attr_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_use_blx(struct elf32_arm_link_hash_table *globals)
{
  if (bfd_elf_get_obj_attr_int (globals->obfd, OBJ_ATTR_PROC,
				Tag_CPU_arch) > 2)
    globals->use_blx = 1;
}