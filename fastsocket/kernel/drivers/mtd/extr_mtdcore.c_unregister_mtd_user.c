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
struct mtd_notifier {int /*<<< orphan*/  list; int /*<<< orphan*/  (* remove ) (scalar_t__) ;} ;

/* Variables and functions */
 int MAX_MTD_DEVICES ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__* mtd_table ; 
 int /*<<< orphan*/  mtd_table_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

int unregister_mtd_user (struct mtd_notifier *old)
{
	int i;

	mutex_lock(&mtd_table_mutex);

	module_put(THIS_MODULE);

	for (i=0; i< MAX_MTD_DEVICES; i++)
		if (mtd_table[i])
			old->remove(mtd_table[i]);

	list_del(&old->list);
	mutex_unlock(&mtd_table_mutex);
	return 0;
}