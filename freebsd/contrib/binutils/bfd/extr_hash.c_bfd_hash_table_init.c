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
struct bfd_hash_table {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_default_hash_table_size ; 
 int /*<<< orphan*/  bfd_hash_table_init_n (struct bfd_hash_table*,struct bfd_hash_entry* (*) (struct bfd_hash_entry*,struct bfd_hash_table*,char const*),unsigned int,int /*<<< orphan*/ ) ; 

bfd_boolean
bfd_hash_table_init (struct bfd_hash_table *table,
		     struct bfd_hash_entry *(*newfunc) (struct bfd_hash_entry *,
							struct bfd_hash_table *,
							const char *),
		     unsigned int entsize)
{
  return bfd_hash_table_init_n (table, newfunc, entsize,
				bfd_default_hash_table_size);
}