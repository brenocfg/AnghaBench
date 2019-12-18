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
struct mtdoops_context {scalar_t__ mtd_index; int /*<<< orphan*/ * mtd; } ;
struct mtd_info {scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_scheduled_work () ; 
 struct mtdoops_context oops_cxt ; 

__attribute__((used)) static void mtdoops_notify_remove(struct mtd_info *mtd)
{
	struct mtdoops_context *cxt = &oops_cxt;

	if ((mtd->index != cxt->mtd_index) || cxt->mtd_index < 0)
		return;

	cxt->mtd = NULL;
	flush_scheduled_work();
}