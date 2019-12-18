#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_hash_table {int /*<<< orphan*/  table; int /*<<< orphan*/  type; int /*<<< orphan*/ * undefs_tail; int /*<<< orphan*/ * undefs; int /*<<< orphan*/  creator; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int /*<<< orphan*/  xvec; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_hash_table_init (int /*<<< orphan*/ *,struct bfd_hash_entry* (*) (struct bfd_hash_entry*,struct bfd_hash_table*,char const*),unsigned int) ; 
 int /*<<< orphan*/  bfd_link_generic_hash_table ; 

bfd_boolean
_bfd_link_hash_table_init
  (struct bfd_link_hash_table *table,
   bfd *abfd,
   struct bfd_hash_entry *(*newfunc) (struct bfd_hash_entry *,
				      struct bfd_hash_table *,
				      const char *),
   unsigned int entsize)
{
  table->creator = abfd->xvec;
  table->undefs = NULL;
  table->undefs_tail = NULL;
  table->type = bfd_link_generic_hash_table;

  return bfd_hash_table_init (&table->table, newfunc, entsize);
}