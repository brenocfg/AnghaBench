#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* bt_foreach_proc ) (TYPE_1__*,void*) ;
typedef  TYPE_2__* binding_table ;
typedef  TYPE_1__* binding_entry ;
struct TYPE_7__ {size_t chain_count; TYPE_1__** chain; } ;
struct TYPE_6__ {struct TYPE_6__* chain; } ;

/* Variables and functions */

void
binding_table_foreach (binding_table table, bt_foreach_proc proc, void *data)
{
  const size_t chain_count = table->chain_count;
  size_t i;

  for (i = 0; i < chain_count; ++i)
    {
      binding_entry entry = table->chain[i];
      for (; entry != NULL; entry = entry->chain)
	proc (entry, data);
    }
}