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
struct queue_elem {struct queue_elem* next; } ;

/* Variables and functions */
 struct queue_elem* define_cond_exec_queue ; 
 scalar_t__ errors ; 
 int /*<<< orphan*/  identify_predicable_attribute () ; 
 int /*<<< orphan*/  process_one_cond_exec (struct queue_elem*) ; 

__attribute__((used)) static void
process_define_cond_exec (void)
{
  struct queue_elem *elem;

  identify_predicable_attribute ();
  if (errors)
    return;

  for (elem = define_cond_exec_queue; elem ; elem = elem->next)
    process_one_cond_exec (elem);
}