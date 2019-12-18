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
typedef  int /*<<< orphan*/  hashnode ;
struct TYPE_3__ {int entries_owned; unsigned int nslots; unsigned int nelements; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ hash_table ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
ht_load (hash_table *ht, hashnode *entries,
	 unsigned int nslots, unsigned int nelements,
	 bool own)
{
  if (ht->entries_owned)
    free (ht->entries);
  ht->entries = entries;
  ht->nslots = nslots;
  ht->nelements = nelements;
  ht->entries_owned = own;
}