#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct observer_list {struct observer_list* next; TYPE_1__* observer; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* notify ) (int /*<<< orphan*/ ,void const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static void
generic_observer_notify (struct observer_list *subject, const void *args)
{
  struct observer_list *current_node = subject;

  while (current_node != NULL)
    {
      (*current_node->observer->notify) (current_node->observer->data, args);
      current_node = current_node->next;
    }
}