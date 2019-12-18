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
typedef  int /*<<< orphan*/  reloc_howto_type ;

/* Variables and functions */
 unsigned int NUM_ELEM (int /*<<< orphan*/ *) ; 
 unsigned int R_ARM_RREL32 ; 
 int /*<<< orphan*/ * elf32_arm_howto_table_1 ; 
 int /*<<< orphan*/ * elf32_arm_howto_table_2 ; 

__attribute__((used)) static reloc_howto_type *
elf32_arm_howto_from_type (unsigned int r_type)
{
  if (r_type < NUM_ELEM (elf32_arm_howto_table_1))
    return &elf32_arm_howto_table_1[r_type];

  if (r_type >= R_ARM_RREL32
      && r_type < R_ARM_RREL32 + NUM_ELEM (elf32_arm_howto_table_2))
    return &elf32_arm_howto_table_2[r_type - R_ARM_RREL32];

  return NULL;
}