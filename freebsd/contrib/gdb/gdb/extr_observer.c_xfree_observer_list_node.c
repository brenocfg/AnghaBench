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
struct observer_list {struct observer_list* observer; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct observer_list*) ; 

__attribute__((used)) static void
xfree_observer_list_node (struct observer_list *node)
{
  xfree (node->observer);
  xfree (node);
}