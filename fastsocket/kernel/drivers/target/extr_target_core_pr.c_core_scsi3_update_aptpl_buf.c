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
typedef  int /*<<< orphan*/  u32 ;
struct se_device {int /*<<< orphan*/  dev_reservation_lock; } ;

/* Variables and functions */
 int __core_scsi3_update_aptpl_buf (struct se_device*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int core_scsi3_update_aptpl_buf(
	struct se_device *dev,
	unsigned char *buf,
	u32 pr_aptpl_buf_len,
	int clear_aptpl_metadata)
{
	int ret;

	spin_lock(&dev->dev_reservation_lock);
	ret = __core_scsi3_update_aptpl_buf(dev, buf, pr_aptpl_buf_len,
				clear_aptpl_metadata);
	spin_unlock(&dev->dev_reservation_lock);

	return ret;
}