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
struct observer_list {struct observer_list* next; struct observer const* observer; } ;
struct observer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  xfree_observer_list_node (struct observer_list*) ; 

__attribute__((used)) static void
generic_observer_detach (struct observer_list **subject,
			 const struct observer *observer)
{
  struct observer_list *previous_node = NULL;
  struct observer_list *current_node = *subject;

  while (current_node != NULL)
    {
      if (current_node->observer == observer)
	{
	  if (previous_node != NULL)
	    previous_node->next = current_node->next;
	  else
	    *subject = current_node->next;
	  xfree_observer_list_node (current_node);
	  return;
	}
      previous_node = current_node;
      current_node = current_node->next;
    }

  /* We should never reach this point.  However, this should not be
     a very serious error, so simply report a warning to the user.  */
  warning ("Failed to detach observer");
}