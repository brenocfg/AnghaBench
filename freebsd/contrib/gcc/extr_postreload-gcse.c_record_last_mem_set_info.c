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
struct modifies_mem {struct modifies_mem* next; int /*<<< orphan*/  insn; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 struct modifies_mem* modifies_mem_list ; 
 int /*<<< orphan*/  modifies_mem_obstack ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
record_last_mem_set_info (rtx insn)
{
  struct modifies_mem *list_entry;

  list_entry = (struct modifies_mem *) obstack_alloc (&modifies_mem_obstack,
						      sizeof (struct modifies_mem));
  list_entry->insn = insn;
  list_entry->next = modifies_mem_list;
  modifies_mem_list = list_entry;
}