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
struct mtd_info {int usecount; int /*<<< orphan*/  owner; int /*<<< orphan*/  (* put_device ) (struct mtd_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_table_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*) ; 

void put_mtd_device(struct mtd_info *mtd)
{
	int c;

	mutex_lock(&mtd_table_mutex);
	c = --mtd->usecount;
	if (mtd->put_device)
		mtd->put_device(mtd);
	mutex_unlock(&mtd_table_mutex);
	BUG_ON(c < 0);

	module_put(mtd->owner);
}