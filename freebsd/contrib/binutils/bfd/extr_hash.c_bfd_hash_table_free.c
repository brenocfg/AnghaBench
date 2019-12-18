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
struct bfd_hash_table {int /*<<< orphan*/ * memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  objalloc_free (int /*<<< orphan*/ *) ; 

void
bfd_hash_table_free (struct bfd_hash_table *table)
{
  objalloc_free (table->memory);
  table->memory = NULL;
}