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
struct ubi_volume_desc {TYPE_1__* vol; } ;
struct ubi_device {int /*<<< orphan*/  ubi_num; } ;
struct file {struct ubi_volume_desc* private_data; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct ubi_device* ubi; } ;

/* Variables and functions */
 int ubi_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vol_cdev_fsync(struct file *file, struct dentry *dentry,
			  int datasync)
{
	struct ubi_volume_desc *desc = file->private_data;
	struct ubi_device *ubi = desc->vol->ubi;

	return ubi_sync(ubi->ubi_num);
}