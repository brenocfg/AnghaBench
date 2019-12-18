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
struct bfd_section_already_linked_hash_entry {struct bfd_section_already_linked* entry; } ;
struct bfd_section_already_linked {struct bfd_section_already_linked* next; int /*<<< orphan*/ * sec; } ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_section_already_linked_table ; 
 struct bfd_section_already_linked* bfd_hash_allocate (int /*<<< orphan*/ *,int) ; 

void
bfd_section_already_linked_table_insert
  (struct bfd_section_already_linked_hash_entry *already_linked_list,
   asection *sec)
{
  struct bfd_section_already_linked *l;

  /* Allocate the memory from the same obstack as the hash table is
     kept in.  */
  l = bfd_hash_allocate (&_bfd_section_already_linked_table, sizeof *l);
  l->sec = sec;
  l->next = already_linked_list->entry;
  already_linked_list->entry = l;
}