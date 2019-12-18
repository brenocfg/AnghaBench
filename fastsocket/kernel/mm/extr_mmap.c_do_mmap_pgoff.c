#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {scalar_t__ map_count; unsigned int def_flags; scalar_t__ locked_vm; } ;
struct inode {int dummy; } ;
struct TYPE_12__ {TYPE_4__* mnt; TYPE_3__* dentry; } ;
struct file {int f_mode; TYPE_6__* f_op; TYPE_5__ f_path; } ;
struct TYPE_14__ {int personality; TYPE_2__* signal; struct mm_struct* mm; } ;
struct TYPE_13__ {int /*<<< orphan*/  mmap; } ;
struct TYPE_11__ {int mnt_flags; } ;
struct TYPE_10__ {struct inode* d_inode; } ;
struct TYPE_9__ {TYPE_1__* rlim; } ;
struct TYPE_8__ {unsigned long rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 unsigned long EACCES ; 
 unsigned long EAGAIN ; 
 unsigned long EINVAL ; 
 unsigned long ENODEV ; 
 unsigned long ENOMEM ; 
 unsigned long EOVERFLOW ; 
 unsigned long EPERM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  IS_APPEND (struct inode*) ; 
 unsigned long MAP_FIXED ; 
 unsigned long MAP_LOCKED ; 
#define  MAP_PRIVATE 129 
#define  MAP_SHARED 128 
 unsigned long MAP_TYPE ; 
 int MNT_NOEXEC ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PROT_EXEC ; 
 unsigned long PROT_READ ; 
 unsigned long PROT_WRITE ; 
 int READ_IMPLIES_EXEC ; 
 size_t RLIMIT_MEMLOCK ; 
 unsigned int VM_EXEC ; 
 unsigned int VM_LOCKED ; 
 unsigned int VM_MAYEXEC ; 
 unsigned int VM_MAYREAD ; 
 unsigned int VM_MAYSHARE ; 
 unsigned int VM_MAYWRITE ; 
 unsigned int VM_SHARED ; 
 unsigned int calc_vm_flag_bits (unsigned long) ; 
 unsigned int calc_vm_prot_bits (unsigned long) ; 
 int /*<<< orphan*/  can_do_mlock () ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_7__* current ; 
 unsigned long get_unmapped_area_prot (struct file*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  locks_verify_locked (struct inode*) ; 
 unsigned long mmap_region (struct file*,unsigned long,unsigned long,unsigned long,unsigned int,unsigned long) ; 
 unsigned long round_hint_to_min (unsigned long) ; 
 int security_file_mmap (struct file*,unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl_max_map_count ; 

unsigned long do_mmap_pgoff(struct file *file, unsigned long addr,
			unsigned long len, unsigned long prot,
			unsigned long flags, unsigned long pgoff)
{
	struct mm_struct * mm = current->mm;
	struct inode *inode;
	unsigned int vm_flags;
	int error;
	unsigned long reqprot = prot;

	/*
	 * Does the application expect PROT_READ to imply PROT_EXEC?
	 *
	 * (the exception is when the underlying filesystem is noexec
	 *  mounted, in which case we dont add PROT_EXEC.)
	 */
	if ((prot & PROT_READ) && (current->personality & READ_IMPLIES_EXEC))
		if (!(file && (file->f_path.mnt->mnt_flags & MNT_NOEXEC)))
			prot |= PROT_EXEC;

	if (!len)
		return -EINVAL;

	if (!(flags & MAP_FIXED))
		addr = round_hint_to_min(addr);

	/* Careful about overflows.. */
	len = PAGE_ALIGN(len);
	if (!len)
		return -ENOMEM;

	/* offset overflow? */
	if ((pgoff + (len >> PAGE_SHIFT)) < pgoff)
               return -EOVERFLOW;

	/* Too many mappings? */
	if (mm->map_count > sysctl_max_map_count)
		return -ENOMEM;

	/* Obtain the address to map to. we verify (or select) it and ensure
	 * that it represents a valid section of the address space.
	 */
	addr = get_unmapped_area_prot(file, addr, len, pgoff, flags,
		prot & PROT_EXEC);
	if (addr & ~PAGE_MASK)
		return addr;

	/* Do simple checking here so the lower-level routines won't have
	 * to. we assume access permissions have been handled by the open
	 * of the memory object, so we don't do any here.
	 */
	vm_flags = calc_vm_prot_bits(prot) | calc_vm_flag_bits(flags) |
			mm->def_flags | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC;

	if (flags & MAP_LOCKED)
		if (!can_do_mlock())
			return -EPERM;

	/* mlock MCL_FUTURE? */
	if (vm_flags & VM_LOCKED) {
		unsigned long locked, lock_limit;
		locked = len >> PAGE_SHIFT;
		locked += mm->locked_vm;
		lock_limit = current->signal->rlim[RLIMIT_MEMLOCK].rlim_cur;
		lock_limit >>= PAGE_SHIFT;
		if (locked > lock_limit && !capable(CAP_IPC_LOCK))
			return -EAGAIN;
	}

	inode = file ? file->f_path.dentry->d_inode : NULL;

	if (file) {
		switch (flags & MAP_TYPE) {
		case MAP_SHARED:
			if ((prot&PROT_WRITE) && !(file->f_mode&FMODE_WRITE))
				return -EACCES;

			/*
			 * Make sure we don't allow writing to an append-only
			 * file..
			 */
			if (IS_APPEND(inode) && (file->f_mode & FMODE_WRITE))
				return -EACCES;

			/*
			 * Make sure there are no mandatory locks on the file.
			 */
			if (locks_verify_locked(inode))
				return -EAGAIN;

			vm_flags |= VM_SHARED | VM_MAYSHARE;
			if (!(file->f_mode & FMODE_WRITE))
				vm_flags &= ~(VM_MAYWRITE | VM_SHARED);

			/* fall through */
		case MAP_PRIVATE:
			if (!(file->f_mode & FMODE_READ))
				return -EACCES;
			if (file->f_path.mnt->mnt_flags & MNT_NOEXEC) {
				if (vm_flags & VM_EXEC)
					return -EPERM;
				vm_flags &= ~VM_MAYEXEC;
			}

			if (!file->f_op || !file->f_op->mmap)
				return -ENODEV;
			break;

		default:
			return -EINVAL;
		}
	} else {
		switch (flags & MAP_TYPE) {
		case MAP_SHARED:
			/*
			 * Ignore pgoff.
			 */
			pgoff = 0;
			vm_flags |= VM_SHARED | VM_MAYSHARE;
			break;
		case MAP_PRIVATE:
			/*
			 * Set pgoff according to addr for anon_vma.
			 */
			pgoff = addr >> PAGE_SHIFT;
			break;
		default:
			return -EINVAL;
		}
	}

	error = security_file_mmap(file, reqprot, prot, flags, addr, 0);
	if (error)
		return error;

	return mmap_region(file, addr, len, flags, vm_flags, pgoff);
}