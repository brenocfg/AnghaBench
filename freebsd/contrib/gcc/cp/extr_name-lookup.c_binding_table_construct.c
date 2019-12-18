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
typedef  TYPE_1__* binding_table ;
struct TYPE_3__ {size_t chain_count; int /*<<< orphan*/  chain; scalar_t__ entry_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GGC_CNEWVEC (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  binding_entry ; 

__attribute__((used)) static inline void
binding_table_construct (binding_table table, size_t chain_count)
{
  table->chain_count = chain_count;
  table->entry_count = 0;
  table->chain = GGC_CNEWVEC (binding_entry, table->chain_count);
}