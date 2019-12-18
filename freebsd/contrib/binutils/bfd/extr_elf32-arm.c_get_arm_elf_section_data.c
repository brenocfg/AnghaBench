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
struct section_list {int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  asection ;
typedef  int /*<<< orphan*/  _arm_elf_section_data ;

/* Variables and functions */
 int /*<<< orphan*/ * elf32_arm_section_data (int /*<<< orphan*/ ) ; 
 struct section_list* find_arm_elf_section_entry (int /*<<< orphan*/ *) ; 

__attribute__((used)) static _arm_elf_section_data *
get_arm_elf_section_data (asection * sec)
{
  struct section_list * entry;

  entry = find_arm_elf_section_entry (sec);

  if (entry)
    return elf32_arm_section_data (entry->sec);
  else
    return NULL;
}