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
struct section_list {struct section_list* prev; struct section_list* next; int /*<<< orphan*/ * sec; } ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 struct section_list* bfd_malloc (int) ; 
 struct section_list* sections_with_arm_elf_section_data ; 

__attribute__((used)) static void
record_section_with_arm_elf_section_data (asection * sec)
{
  struct section_list * entry;

  entry = bfd_malloc (sizeof (* entry));
  if (entry == NULL)
    return;
  entry->sec = sec;
  entry->next = sections_with_arm_elf_section_data;
  entry->prev = NULL;
  if (entry->next != NULL)
    entry->next->prev = entry;
  sections_with_arm_elf_section_data = entry;
}