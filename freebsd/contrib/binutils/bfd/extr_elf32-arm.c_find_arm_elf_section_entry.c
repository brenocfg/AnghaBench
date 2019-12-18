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
struct section_list {struct section_list* prev; int /*<<< orphan*/ * sec; struct section_list* next; } ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 struct section_list* sections_with_arm_elf_section_data ; 

__attribute__((used)) static struct section_list *
find_arm_elf_section_entry (asection * sec)
{
  struct section_list * entry;
  static struct section_list * last_entry = NULL;

  /* This is a short cut for the typical case where the sections are added
     to the sections_with_arm_elf_section_data list in forward order and
     then looked up here in backwards order.  This makes a real difference
     to the ld-srec/sec64k.exp linker test.  */
  entry = sections_with_arm_elf_section_data;
  if (last_entry != NULL)
    {
      if (last_entry->sec == sec)
	entry = last_entry;
      else if (last_entry->next != NULL
	       && last_entry->next->sec == sec)
	entry = last_entry->next;
    }

  for (; entry; entry = entry->next)
    if (entry->sec == sec)
      break;

  if (entry)
    /* Record the entry prior to this one - it is the entry we are most
       likely to want to locate next time.  Also this way if we have been
       called from unrecord_section_with_arm_elf_section_data() we will not
       be caching a pointer that is about to be freed.  */
    last_entry = entry->prev;

  return entry;
}