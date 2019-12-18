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
struct spu_link_hash_table {int /*<<< orphan*/  stub_hash_table; } ;
struct bfd_link_hash_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_generic_link_hash_table_free (struct bfd_link_hash_table*) ; 
 int /*<<< orphan*/  bfd_hash_table_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spu_elf_link_hash_table_free (struct bfd_link_hash_table *hash)
{
  struct spu_link_hash_table *ret = (struct spu_link_hash_table *) hash;

  bfd_hash_table_free (&ret->stub_hash_table);
  _bfd_generic_link_hash_table_free (hash);
}