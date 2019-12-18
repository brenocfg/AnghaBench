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
struct reggroups {struct reggroup_el** last; } ;
struct reggroup_el {struct reggroup_el* next; struct reggroup* group; } ;
struct reggroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_group (struct reggroups *groups, struct reggroup *group,
	   struct reggroup_el *el)
{
  gdb_assert (group != NULL);
  el->group = group;
  el->next = NULL;
  (*groups->last) = el;
  groups->last = &el->next;
}