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
struct inode {int dummy; } ;
struct file {TYPE_1__* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ scsi_changer ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_device_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ch_release(struct inode *inode, struct file *file)
{
	scsi_changer *ch = file->private_data;

	scsi_device_put(ch->device);
	file->private_data = NULL;
	return 0;
}