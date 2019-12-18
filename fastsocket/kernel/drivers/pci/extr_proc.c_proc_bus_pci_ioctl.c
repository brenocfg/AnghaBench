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
struct proc_dir_entry {struct pci_dev* data; } ;
struct pci_filp_private {int write_combine; int /*<<< orphan*/  mmap_state; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct file {struct pci_filp_private* private_data; TYPE_1__* f_dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PCIIOC_CONTROLLER 131 
#define  PCIIOC_MMAP_IS_IO 130 
#define  PCIIOC_MMAP_IS_MEM 129 
#define  PCIIOC_WRITE_COMBINE 128 
 struct proc_dir_entry* PDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int pci_domain_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_mmap_io ; 
 int /*<<< orphan*/  pci_mmap_mem ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static long proc_bus_pci_ioctl(struct file *file, unsigned int cmd,
			       unsigned long arg)
{
	const struct proc_dir_entry *dp = PDE(file->f_dentry->d_inode);
	struct pci_dev *dev = dp->data;
#ifdef HAVE_PCI_MMAP
	struct pci_filp_private *fpriv = file->private_data;
#endif /* HAVE_PCI_MMAP */
	int ret = 0;

	lock_kernel();

	switch (cmd) {
	case PCIIOC_CONTROLLER:
		ret = pci_domain_nr(dev->bus);
		break;

#ifdef HAVE_PCI_MMAP
	case PCIIOC_MMAP_IS_IO:
		fpriv->mmap_state = pci_mmap_io;
		break;

	case PCIIOC_MMAP_IS_MEM:
		fpriv->mmap_state = pci_mmap_mem;
		break;

	case PCIIOC_WRITE_COMBINE:
		if (arg)
			fpriv->write_combine = 1;
		else
			fpriv->write_combine = 0;
		break;

#endif /* HAVE_PCI_MMAP */

	default:
		ret = -EINVAL;
		break;
	};

	unlock_kernel();
	return ret;
}