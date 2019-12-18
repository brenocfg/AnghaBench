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
struct mtd_info {int /*<<< orphan*/  (* resume ) (struct mtd_info*) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mtd_info* dev_to_mtd (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*) ; 

__attribute__((used)) static int mtd_cls_resume(struct device *dev)
{
	struct mtd_info *mtd = dev_to_mtd(dev);
	
	if (mtd && mtd->resume)
		mtd->resume(mtd);
	return 0;
}