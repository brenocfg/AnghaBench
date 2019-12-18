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
struct vm_area_struct {int vm_flags; struct usX2Ydev* vm_private_data; int /*<<< orphan*/ * vm_ops; scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct usX2Ydev {int chip_status; int /*<<< orphan*/  hwdep_pcm_shm; } ;
struct snd_usX2Y_hwdep_pcm_shm {int dummy; } ;
struct snd_hwdep {struct usX2Ydev* private_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 unsigned long PAGE_ALIGN (int) ; 
 int USX2Y_STAT_CHIP_INIT ; 
 int VM_DONTEXPAND ; 
 int VM_RESERVED ; 
 int /*<<< orphan*/  snd_printd (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  snd_usX2Y_hwdep_pcm_vm_ops ; 

__attribute__((used)) static int snd_usX2Y_hwdep_pcm_mmap(struct snd_hwdep * hw, struct file *filp, struct vm_area_struct *area)
{
	unsigned long	size = (unsigned long)(area->vm_end - area->vm_start);
	struct usX2Ydev	*usX2Y = hw->private_data;

	if (!(usX2Y->chip_status & USX2Y_STAT_CHIP_INIT))
		return -EBUSY;

	/* if userspace tries to mmap beyond end of our buffer, fail */ 
	if (size > PAGE_ALIGN(sizeof(struct snd_usX2Y_hwdep_pcm_shm))) {
		snd_printd("%lu > %lu\n", size, (unsigned long)sizeof(struct snd_usX2Y_hwdep_pcm_shm)); 
		return -EINVAL;
	}

	if (!usX2Y->hwdep_pcm_shm) {
		return -ENODEV;
	}
	area->vm_ops = &snd_usX2Y_hwdep_pcm_vm_ops;
	area->vm_flags |= VM_RESERVED | VM_DONTEXPAND;
	area->vm_private_data = hw->private_data;
	return 0;
}