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
struct elevator_type {int /*<<< orphan*/  elevator_owner; } ;

/* Variables and functions */
 int ELV_NAME_MAX ; 
 struct elevator_type* elevator_find (char const*) ; 
 int /*<<< orphan*/  elv_list_lock ; 
 int /*<<< orphan*/  request_module (char*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct elevator_type *elevator_get(const char *name)
{
	struct elevator_type *e;

	spin_lock(&elv_list_lock);

	e = elevator_find(name);
	if (!e) {
		char elv[ELV_NAME_MAX + strlen("-iosched")];

		spin_unlock(&elv_list_lock);

		if (!strcmp(name, "anticipatory"))
			sprintf(elv, "as-iosched");
		else
			sprintf(elv, "%s-iosched", name);

		request_module("%s", elv);
		spin_lock(&elv_list_lock);
		e = elevator_find(name);
	}

	if (e && !try_module_get(e->elevator_owner))
		e = NULL;

	spin_unlock(&elv_list_lock);

	return e;
}