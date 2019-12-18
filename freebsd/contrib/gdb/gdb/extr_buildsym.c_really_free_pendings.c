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
struct pending {struct pending* next; } ;

/* Variables and functions */
 struct pending* file_symbols ; 
 int /*<<< orphan*/  free_macro_table (scalar_t__) ; 
 int /*<<< orphan*/  free_pending_blocks () ; 
 struct pending* free_pendings ; 
 struct pending* global_symbols ; 
 scalar_t__ pending_macros ; 
 int /*<<< orphan*/  xfree (void*) ; 

void
really_free_pendings (void *dummy)
{
  struct pending *next, *next1;

  for (next = free_pendings; next; next = next1)
    {
      next1 = next->next;
      xfree ((void *) next);
    }
  free_pendings = NULL;

  free_pending_blocks ();

  for (next = file_symbols; next != NULL; next = next1)
    {
      next1 = next->next;
      xfree ((void *) next);
    }
  file_symbols = NULL;

  for (next = global_symbols; next != NULL; next = next1)
    {
      next1 = next->next;
      xfree ((void *) next);
    }
  global_symbols = NULL;

  if (pending_macros)
    free_macro_table (pending_macros);
}