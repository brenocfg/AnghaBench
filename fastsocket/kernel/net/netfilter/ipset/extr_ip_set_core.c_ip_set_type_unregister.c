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
struct ip_set_type {int /*<<< orphan*/  revision; int /*<<< orphan*/  family; int /*<<< orphan*/  name; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  family_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_set_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_type_lock () ; 
 int /*<<< orphan*/  ip_set_type_unlock () ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void
ip_set_type_unregister(struct ip_set_type *type)
{
	ip_set_type_lock();
	if (!find_set_type(type->name, type->family, type->revision)) {
		pr_warning("ip_set type %s, family %s, revision %u "
			   "not registered\n", type->name,
			   family_name(type->family), type->revision);
		goto unlock;
	}
	list_del_rcu(&type->list);
	pr_debug("type %s, family %s, revision %u unregistered.\n",
		 type->name, family_name(type->family), type->revision);
unlock:
	ip_set_type_unlock();

	synchronize_rcu();
}