#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  table; } ;
struct generic_link_hash_table {TYPE_1__ root; } ;
struct bfd_link_hash_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_hash_table_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct generic_link_hash_table*) ; 

void
_bfd_generic_link_hash_table_free (struct bfd_link_hash_table *hash)
{
  struct generic_link_hash_table *ret
    = (struct generic_link_hash_table *) hash;

  bfd_hash_table_free (&ret->root.table);
  free (ret);
}