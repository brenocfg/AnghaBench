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
struct mtd_notifier {int /*<<< orphan*/  (* add ) (scalar_t__) ;int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int MAX_MTD_DEVICES ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtd_notifiers ; 
 scalar_t__* mtd_table ; 
 int /*<<< orphan*/  mtd_table_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void register_mtd_user (struct mtd_notifier *new)
{
	int i;

	mutex_lock(&mtd_table_mutex);

	list_add(&new->list, &mtd_notifiers);

 	__module_get(THIS_MODULE);

	for (i=0; i< MAX_MTD_DEVICES; i++)
		if (mtd_table[i])
			new->add(mtd_table[i]);

	mutex_unlock(&mtd_table_mutex);
}