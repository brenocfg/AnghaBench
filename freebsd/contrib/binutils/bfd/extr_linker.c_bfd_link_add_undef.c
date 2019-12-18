#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_hash_table {struct bfd_link_hash_entry* undefs_tail; struct bfd_link_hash_entry* undefs; } ;
struct TYPE_3__ {struct bfd_link_hash_entry* next; } ;
struct TYPE_4__ {TYPE_1__ undef; } ;
struct bfd_link_hash_entry {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 

void
bfd_link_add_undef (struct bfd_link_hash_table *table,
		    struct bfd_link_hash_entry *h)
{
  BFD_ASSERT (h->u.undef.next == NULL);
  if (table->undefs_tail != NULL)
    table->undefs_tail->u.undef.next = h;
  if (table->undefs == NULL)
    table->undefs = h;
  table->undefs_tail = h;
}