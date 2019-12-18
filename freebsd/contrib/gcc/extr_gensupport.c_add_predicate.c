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
struct pred_data {struct pred_data* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 void** htab_find_slot (int /*<<< orphan*/ ,struct pred_data*,int /*<<< orphan*/ ) ; 
 struct pred_data** last_predicate ; 
 int /*<<< orphan*/  predicate_table ; 

void
add_predicate (struct pred_data *pred)
{
  void **slot = htab_find_slot (predicate_table, pred, INSERT);
  if (*slot)
    {
      error ("duplicate predicate definition for '%s'", pred->name);
      return;
    }
  *slot = pred;
  *last_predicate = pred;
  last_predicate = &pred->next;
}