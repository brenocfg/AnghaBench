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
struct genl_family {int /*<<< orphan*/  list; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int genl_unregister_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

int compat_genl_unregister_family(struct genl_family *family)
{
	int err;
	err = genl_unregister_family(&family->family);
	list_del(&family->list);
	return err;
}