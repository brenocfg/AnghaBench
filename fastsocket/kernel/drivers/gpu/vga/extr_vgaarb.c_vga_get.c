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
typedef  int /*<<< orphan*/  wait_queue_t ;
struct vga_device {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EINTR ; 
 int ENODEV ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 struct vga_device* __vga_tryget (struct vga_device*,unsigned int) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vga_check_first_use () ; 
 struct pci_dev* vga_default_device () ; 
 int /*<<< orphan*/  vga_lock ; 
 int /*<<< orphan*/  vga_wait_queue ; 
 struct vga_device* vgadev_find (struct pci_dev*) ; 

int vga_get(struct pci_dev *pdev, unsigned int rsrc, int interruptible)
{
	struct vga_device *vgadev, *conflict;
	unsigned long flags;
	wait_queue_t wait;
	int rc = 0;

	vga_check_first_use();
	/* The one who calls us should check for this, but lets be sure... */
	if (pdev == NULL)
		pdev = vga_default_device();
	if (pdev == NULL)
		return 0;

	for (;;) {
		spin_lock_irqsave(&vga_lock, flags);
		vgadev = vgadev_find(pdev);
		if (vgadev == NULL) {
			spin_unlock_irqrestore(&vga_lock, flags);
			rc = -ENODEV;
			break;
		}
		conflict = __vga_tryget(vgadev, rsrc);
		spin_unlock_irqrestore(&vga_lock, flags);
		if (conflict == NULL)
			break;


		/* We have a conflict, we wait until somebody kicks the
		 * work queue. Currently we have one work queue that we
		 * kick each time some resources are released, but it would
		 * be fairly easy to have a per device one so that we only
		 * need to attach to the conflicting device
		 */
		init_waitqueue_entry(&wait, current);
		add_wait_queue(&vga_wait_queue, &wait);
		set_current_state(interruptible ?
				  TASK_INTERRUPTIBLE :
				  TASK_UNINTERRUPTIBLE);
		if (signal_pending(current)) {
			rc = -EINTR;
			break;
		}
		schedule();
		remove_wait_queue(&vga_wait_queue, &wait);
		set_current_state(TASK_RUNNING);
	}
	return rc;
}