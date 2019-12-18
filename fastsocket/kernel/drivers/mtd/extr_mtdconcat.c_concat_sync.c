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
struct mtd_info {int /*<<< orphan*/  (* sync ) (struct mtd_info*) ;} ;
struct mtd_concat {int num_subdev; struct mtd_info** subdev; } ;

/* Variables and functions */
 struct mtd_concat* CONCAT (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*) ; 

__attribute__((used)) static void concat_sync(struct mtd_info *mtd)
{
	struct mtd_concat *concat = CONCAT(mtd);
	int i;

	for (i = 0; i < concat->num_subdev; i++) {
		struct mtd_info *subdev = concat->subdev[i];
		subdev->sync(subdev);
	}
}