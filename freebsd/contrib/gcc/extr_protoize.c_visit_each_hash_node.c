#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__ const* hash_next; scalar_t__ symbol; } ;
typedef  TYPE_1__ const hash_table_entry ;

/* Variables and functions */
 size_t HASH_TABLE_SIZE ; 
 void stub1 (TYPE_1__ const*) ; 
 void stub2 (TYPE_1__ const*) ; 

__attribute__((used)) static void
visit_each_hash_node (const hash_table_entry *hash_tab_p,
		      void (*func) (const hash_table_entry *))
{
  const hash_table_entry *primary;

  for (primary = hash_tab_p; primary < &hash_tab_p[HASH_TABLE_SIZE]; primary++)
    if (primary->symbol)
      {
	hash_table_entry *second;

	(*func)(primary);
	for (second = primary->hash_next; second; second = second->hash_next)
	  (*func) (second);
      }
}