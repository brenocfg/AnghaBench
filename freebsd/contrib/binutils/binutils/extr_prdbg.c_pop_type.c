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
struct pr_stack {char* type; struct pr_stack* next; } ;
struct pr_handle {struct pr_stack* stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pr_stack*) ; 

__attribute__((used)) static char *
pop_type (struct pr_handle *info)
{
  struct pr_stack *o;
  char *ret;

  assert (info->stack != NULL);

  o = info->stack;
  info->stack = o->next;
  ret = o->type;
  free (o);

  return ret;
}