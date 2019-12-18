#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_flags; struct usX2Ydev* vm_private_data; int /*<<< orphan*/ * vm_ops; scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct usX2Ydev {int chip_status; TYPE_1__* us428ctls_sharedmem; int /*<<< orphan*/  us428ctls_wait_queue_head; } ;
struct us428ctls_sharedmem {int dummy; } ;
struct snd_hwdep {struct usX2Ydev* private_data; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int CtlSnapShotLast; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_ALIGN (int) ; 
 int USX2Y_STAT_CHIP_INIT ; 
 int VM_DONTEXPAND ; 
 int VM_RESERVED ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 TYPE_1__* snd_malloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printd (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  us428ctls_vm_ops ; 

__attribute__((used)) static int snd_us428ctls_mmap(struct snd_hwdep * hw, struct file *filp, struct vm_area_struct *area)
{
	unsigned long	size = (unsigned long)(area->vm_end - area->vm_start);
	struct usX2Ydev	*us428 = hw->private_data;

	// FIXME this hwdep interface is used twice: fpga download and mmap for controlling Lights etc. Maybe better using 2 hwdep devs?
	// so as long as the device isn't fully initialised yet we return -EBUSY here.
 	if (!(us428->chip_status & USX2Y_STAT_CHIP_INIT))
		return -EBUSY;

	/* if userspace tries to mmap beyond end of our buffer, fail */ 
        if (size > PAGE_ALIGN(sizeof(struct us428ctls_sharedmem))) {
		snd_printd( "%lu > %lu\n", size, (unsigned long)sizeof(struct us428ctls_sharedmem)); 
                return -EINVAL;
	}

	if (!us428->us428ctls_sharedmem) {
		init_waitqueue_head(&us428->us428ctls_wait_queue_head);
		if(!(us428->us428ctls_sharedmem = snd_malloc_pages(sizeof(struct us428ctls_sharedmem), GFP_KERNEL)))
			return -ENOMEM;
		memset(us428->us428ctls_sharedmem, -1, sizeof(struct us428ctls_sharedmem));
		us428->us428ctls_sharedmem->CtlSnapShotLast = -2;
	}
	area->vm_ops = &us428ctls_vm_ops;
	area->vm_flags |= VM_RESERVED | VM_DONTEXPAND;
	area->vm_private_data = hw->private_data;
	return 0;
}