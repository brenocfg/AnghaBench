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
struct TYPE_3__ {int tweaking; } ;
typedef  TYPE_1__ file ;

/* Variables and functions */
 struct file_stack_entry* file_stack ; 
 int /*<<< orphan*/  file_stack_obstack ; 
 struct file_stack_entry* obstack_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
file_push (file *p)
{
  struct file_stack_entry *ep;

  if (p->tweaking)
    return;

  ep = obstack_alloc
    (&file_stack_obstack, sizeof (struct file_stack_entry));
  ep->value = p;
  ep->next = file_stack;
  file_stack = ep;
  p->tweaking = 1;
}