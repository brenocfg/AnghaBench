#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubi_device {TYPE_1__* mtd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sync ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 struct ubi_device* ubi_get_device (int) ; 
 int /*<<< orphan*/  ubi_put_device (struct ubi_device*) ; 

int ubi_sync(int ubi_num)
{
	struct ubi_device *ubi;

	ubi = ubi_get_device(ubi_num);
	if (!ubi)
		return -ENODEV;

	if (ubi->mtd->sync)
		ubi->mtd->sync(ubi->mtd);

	ubi_put_device(ubi);
	return 0;
}