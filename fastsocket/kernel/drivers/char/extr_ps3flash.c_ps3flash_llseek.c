#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ps3_storage_device {size_t region_idx; int blk_size; TYPE_1__* regions; } ;
struct file {scalar_t__ f_pos; TYPE_2__* f_mapping; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_5__ {TYPE_3__* host; } ;
struct TYPE_4__ {int size; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ps3_storage_device* ps3flash_dev ; 

__attribute__((used)) static loff_t ps3flash_llseek(struct file *file, loff_t offset, int origin)
{
	struct ps3_storage_device *dev = ps3flash_dev;
	loff_t res;

	mutex_lock(&file->f_mapping->host->i_mutex);
	switch (origin) {
	case 1:
		offset += file->f_pos;
		break;
	case 2:
		offset += dev->regions[dev->region_idx].size*dev->blk_size;
		break;
	}
	if (offset < 0) {
		res = -EINVAL;
		goto out;
	}

	file->f_pos = offset;
	res = file->f_pos;

out:
	mutex_unlock(&file->f_mapping->host->i_mutex);
	return res;
}