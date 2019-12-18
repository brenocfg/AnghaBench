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
struct table_elt {scalar_t__ in_memory; struct table_elt* next_same_hash; } ;

/* Variables and functions */
 int HASH_SIZE ; 
 int /*<<< orphan*/  remove_from_table (struct table_elt*,int) ; 
 struct table_elt** table ; 

__attribute__((used)) static void
invalidate_memory (void)
{
  int i;
  struct table_elt *p, *next;

  for (i = 0; i < HASH_SIZE; i++)
    for (p = table[i]; p; p = next)
      {
	next = p->next_same_hash;
	if (p->in_memory)
	  remove_from_table (p, i);
      }
}