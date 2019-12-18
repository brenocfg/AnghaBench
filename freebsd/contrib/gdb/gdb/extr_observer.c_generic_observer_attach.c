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
struct observer_list {struct observer* observer; struct observer_list* next; } ;
struct observer {void* data; int /*<<< orphan*/ * notify; } ;
typedef  int /*<<< orphan*/  generic_observer_notification_ftype ;

/* Variables and functions */
 struct observer_list* xalloc_observer_list_node () ; 

__attribute__((used)) static struct observer *
generic_observer_attach (struct observer_list **subject,
			 generic_observer_notification_ftype * notify,
			 void *data)
{
  struct observer_list *observer_list = xalloc_observer_list_node ();

  observer_list->next = *subject;
  observer_list->observer->notify = notify;
  observer_list->observer->data = data;
  *subject = observer_list;

  return observer_list->observer;
}