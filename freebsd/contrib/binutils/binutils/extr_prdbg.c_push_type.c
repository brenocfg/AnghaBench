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
struct pr_stack {struct pr_stack* next; int /*<<< orphan*/ * method; int /*<<< orphan*/  visibility; int /*<<< orphan*/  type; } ;
struct pr_handle {struct pr_stack* stack; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_VISIBILITY_IGNORE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (struct pr_stack*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static bfd_boolean
push_type (struct pr_handle *info, const char *type)
{
  struct pr_stack *n;

  if (type == NULL)
    return FALSE;

  n = (struct pr_stack *) xmalloc (sizeof *n);
  memset (n, 0, sizeof *n);

  n->type = xstrdup (type);
  n->visibility = DEBUG_VISIBILITY_IGNORE;
  n->method = NULL;
  n->next = info->stack;
  info->stack = n;

  return TRUE;
}