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
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  o_excl_wait; scalar_t__ exclude; TYPE_1__* disk; } ;
struct TYPE_5__ {int closed; int /*<<< orphan*/  f_ref; TYPE_3__* parentdp; } ;
struct TYPE_4__ {int /*<<< orphan*/  disk_name; } ;
typedef  TYPE_2__ Sg_fd ;
typedef  TYPE_3__ Sg_device ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SCSI_LOG_TIMEOUT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_remove_sfp ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sg_release(struct inode *inode, struct file *filp)
{
	Sg_device *sdp;
	Sg_fd *sfp;

	if ((!(sfp = (Sg_fd *) filp->private_data)) || (!(sdp = sfp->parentdp)))
		return -ENXIO;
	SCSI_LOG_TIMEOUT(3, printk("sg_release: %s\n", sdp->disk->disk_name));

	sfp->closed = 1;

	sdp->exclude = 0;
	wake_up_interruptible(&sdp->o_excl_wait);

	kref_put(&sfp->f_ref, sg_remove_sfp);
	return 0;
}