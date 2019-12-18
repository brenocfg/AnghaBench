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
struct file_stack_entry {struct file_stack_entry* next; TYPE_1__* value; } ;
struct TYPE_3__ {scalar_t__ tweaking; } ;
typedef  TYPE_1__ file ;

/* Variables and functions */
 struct file_stack_entry* file_stack ; 
 int /*<<< orphan*/  file_stack_obstack ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,struct file_stack_entry*) ; 

__attribute__((used)) static file *
file_pop (void)
{
  struct file_stack_entry *ep = file_stack;
  file *p;
  if (ep == NULL)
    return NULL;
  p = ep->value;
  file_stack = ep->next;
  obstack_free (&file_stack_obstack, ep);
  p->tweaking = 0;
  return p;
}