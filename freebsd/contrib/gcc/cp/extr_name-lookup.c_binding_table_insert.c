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
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* binding_table ;
typedef  TYPE_2__* binding_entry ;
struct TYPE_7__ {struct TYPE_7__* chain; } ;
struct TYPE_6__ {int chain_count; int entry_count; TYPE_2__** chain; } ;

/* Variables and functions */
 size_t ENTRY_INDEX (unsigned int const,int) ; 
 unsigned int IDENTIFIER_HASH_VALUE (int /*<<< orphan*/ ) ; 
 TYPE_2__* binding_entry_make (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binding_table_expand (TYPE_1__*) ; 

__attribute__((used)) static void
binding_table_insert (binding_table table, tree name, tree type)
{
  const unsigned int hash = IDENTIFIER_HASH_VALUE (name);
  const size_t i = ENTRY_INDEX (hash, table->chain_count);
  binding_entry entry = binding_entry_make (name, type);

  entry->chain = table->chain[i];
  table->chain[i] = entry;
  ++table->entry_count;

  if (3 * table->chain_count < 5 * table->entry_count)
    binding_table_expand (table);
}