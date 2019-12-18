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
struct bfd_link_hash_table {int /*<<< orphan*/  table; } ;
struct TYPE_4__ {struct bfd_link_hash_entry* link; } ;
struct TYPE_3__ {TYPE_2__ i; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_1__ u; } ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ bfd_hash_lookup (int /*<<< orphan*/ *,char const*,scalar_t__,scalar_t__) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 

struct bfd_link_hash_entry *
bfd_link_hash_lookup (struct bfd_link_hash_table *table,
		      const char *string,
		      bfd_boolean create,
		      bfd_boolean copy,
		      bfd_boolean follow)
{
  struct bfd_link_hash_entry *ret;

  ret = ((struct bfd_link_hash_entry *)
	 bfd_hash_lookup (&table->table, string, create, copy));

  if (follow && ret != NULL)
    {
      while (ret->type == bfd_link_hash_indirect
	     || ret->type == bfd_link_hash_warning)
	ret = ret->u.i.link;
    }

  return ret;
}