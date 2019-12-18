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
struct ub_lun {struct ub_dev* udev; } ;
struct ub_dev {int dummy; } ;
struct gendisk {struct ub_lun* private_data; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ub_put (struct ub_dev*) ; 

__attribute__((used)) static int ub_bd_release(struct gendisk *disk, fmode_t mode)
{
	struct ub_lun *lun = disk->private_data;
	struct ub_dev *sc = lun->udev;

	ub_put(sc);
	return 0;
}