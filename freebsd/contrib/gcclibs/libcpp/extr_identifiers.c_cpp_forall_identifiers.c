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
typedef  int /*<<< orphan*/  ht_cb ;
struct TYPE_3__ {int /*<<< orphan*/  hash_table; } ;
typedef  TYPE_1__ cpp_reader ;
typedef  scalar_t__ cpp_cb ;

/* Variables and functions */
 int /*<<< orphan*/  ht_forall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void
cpp_forall_identifiers (cpp_reader *pfile, cpp_cb cb, void *v)
{
  /* We don't need a proxy since the hash table's identifier comes
     first in cpp_hashnode.  */
  ht_forall (pfile->hash_table, (ht_cb) cb, v);
}