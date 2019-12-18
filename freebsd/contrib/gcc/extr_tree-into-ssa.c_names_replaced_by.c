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
typedef  int /*<<< orphan*/  tree ;
struct repl_map_d {int /*<<< orphan*/ * set; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/ * bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  NO_INSERT ; 
 void** htab_find_slot (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repl_tbl ; 

__attribute__((used)) static inline bitmap
names_replaced_by (tree new)
{
  struct repl_map_d m;
  void **slot;

  m.name = new;
  slot = htab_find_slot (repl_tbl, (void *) &m, NO_INSERT);

  /* If N was not registered in the replacement table, return NULL.  */
  if (slot == NULL || *slot == NULL)
    return NULL;

  return ((struct repl_map_d *) *slot)->set;
}