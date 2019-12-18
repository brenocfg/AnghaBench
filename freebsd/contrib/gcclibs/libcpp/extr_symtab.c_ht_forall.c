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
typedef  scalar_t__ (* ht_cb ) (int /*<<< orphan*/ ,scalar_t__,void const*) ;
typedef  scalar_t__ hashnode ;
struct TYPE_3__ {int nslots; int /*<<< orphan*/  pfile; scalar_t__* entries; } ;
typedef  TYPE_1__ hash_table ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__,void const*) ; 

void
ht_forall (hash_table *table, ht_cb cb, const void *v)
{
  hashnode *p, *limit;

  p = table->entries;
  limit = p + table->nslots;
  do
    if (*p)
      {
	if ((*cb) (table->pfile, *p, v) == 0)
	  break;
      }
  while (++p < limit);
}