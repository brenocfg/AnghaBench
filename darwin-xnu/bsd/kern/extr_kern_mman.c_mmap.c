#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_tag_t ;
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
struct TYPE_17__ {void* vmkf_map_jit; } ;
typedef  TYPE_2__ vm_map_kernel_flags_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  scalar_t__ user_size_t ;
typedef  int user_addr_t ;
typedef  int uint32_t ;
struct vnode_attr {int /*<<< orphan*/  va_access_time; } ;
struct vnode {scalar_t__ v_type; } ;
struct mmap_args {int fd; int addr; int prot; int flags; scalar_t__ pos; scalar_t__ len; } ;
struct fileproc {TYPE_10__* f_fglob; } ;
typedef  TYPE_3__* proc_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ memory_object_t ;
typedef  int /*<<< orphan*/ * memory_object_control_t ;
typedef  int kern_return_t ;
typedef  void* boolean_t ;
struct TYPE_18__ {TYPE_1__* p_vmspace; } ;
struct TYPE_16__ {scalar_t__ vm_daddr; } ;
struct TYPE_15__ {int fg_flag; scalar_t__ fg_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_VNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG (scalar_t__,...) ; 
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_BSD_SC_EXTENDED_INFO ; 
 int /*<<< orphan*/  DBG_BSD_SC_EXTENDED_INFO2 ; 
 int DBG_FUNC_NONE ; 
#define  DTYPE_PSXSHM 133 
#define  DTYPE_VNODE 132 
 int EACCES ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 void* FALSE ; 
 int FILEGLOB_DTYPE (TYPE_10__*) ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  IPC_PORT_NULL ; 
 int /*<<< orphan*/  KAUTH_VNODE_CHECKIMMUTABLE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int,int,int,int,int /*<<< orphan*/ ) ; 
#define  KERN_INVALID_ADDRESS 131 
#define  KERN_NO_SPACE 130 
#define  KERN_PROTECTION_FAILURE 129 
#define  KERN_SUCCESS 128 
 int MAP_ANON ; 
 int MAP_FIXED ; 
 int MAP_JIT ; 
 int MAP_NOCACHE ; 
 int MAP_RESILIENT_CODESIGN ; 
 int MAP_RESILIENT_MEDIA ; 
 int MAP_SHARED ; 
 scalar_t__ MAXDSIZ ; 
 scalar_t__ MEMORY_OBJECT_NULL ; 
 int MNT_NOATIME ; 
 struct vnode* NULLVP ; 
 scalar_t__ PAGE_SIZE_64 ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SYS_mmap ; 
 void* TRUE ; 
 int /*<<< orphan*/  UBC_FLAGS_NONE ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VCHR ; 
 int VM_FLAGS_4GB_CHUNK ; 
 int VM_FLAGS_ALIAS_MASK ; 
 int VM_FLAGS_ANYWHERE ; 
 int VM_FLAGS_FIXED ; 
 int VM_FLAGS_NO_CACHE ; 
 int VM_FLAGS_OVERWRITE ; 
 int VM_FLAGS_PURGABLE ; 
 int VM_FLAGS_RESILIENT_CODESIGN ; 
 int VM_FLAGS_SUPERPAGE_MASK ; 
 int /*<<< orphan*/  VM_GET_FLAGS_ALIAS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  VM_INHERIT_SHARE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 TYPE_2__ VM_MAP_KERNEL_FLAGS_NONE ; 
 int VM_PROT_ALL ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 scalar_t__ VREG ; 
 scalar_t__ VSTR ; 
 scalar_t__ addr ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_map () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  fp_drop (TYPE_3__*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_lookup (TYPE_3__*,int,struct fileproc**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 int mac_file_check_mmap (int /*<<< orphan*/ ,TYPE_10__*,int,int,scalar_t__,int*) ; 
 int mac_proc_check_map_anon (TYPE_3__*,scalar_t__,scalar_t__,int,int,int*) ; 
 int /*<<< orphan*/  memory_object_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  nanotime (int /*<<< orphan*/ *) ; 
 scalar_t__ os_add_overflow (scalar_t__,scalar_t__,scalar_t__*) ; 
 int pshm_mmap (TYPE_3__*,struct mmap_args*,int*,struct fileproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * swapfile_pager_control (scalar_t__) ; 
 scalar_t__ swapfile_pager_setup (struct vnode*) ; 
 int /*<<< orphan*/ * ubc_getobject (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_setthreadcred (struct vnode*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_access_time ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vm_map_enter_mem_object (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int,int /*<<< orphan*/ ) ; 
 int vm_map_enter_mem_object_control (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,void*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_page_mask (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_page_size (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_round_page (scalar_t__,scalar_t__) ; 
 scalar_t__ vm_map_trunc_page (scalar_t__,scalar_t__) ; 
 int vnode_authorize (struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vnode_getwithref (struct vnode*) ; 
 scalar_t__ vnode_isswap (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int /*<<< orphan*/  vnode_setattr (struct vnode*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int vnode_vfsvisflags (struct vnode*) ; 
 int /*<<< orphan*/  vnpath ; 

int
mmap(proc_t p, struct mmap_args *uap, user_addr_t *retval)
{
	/*
	 *	Map in special device (must be SHARED) or file
	 */
	struct fileproc *fp;
	struct			vnode *vp;
	int			flags;
	int			prot;
	int			err=0;
	vm_map_t		user_map;
	kern_return_t		result;
	vm_map_offset_t		user_addr;
	vm_map_size_t		user_size;
	vm_object_offset_t	pageoff;
	vm_object_offset_t	file_pos;
	int			alloc_flags = 0;
	vm_tag_t		tag = VM_KERN_MEMORY_NONE;
	vm_map_kernel_flags_t	vmk_flags = VM_MAP_KERNEL_FLAGS_NONE;
	boolean_t		docow;
	vm_prot_t		maxprot;
	void 			*handle;
	memory_object_t		pager = MEMORY_OBJECT_NULL;
	memory_object_control_t	 control;
	int 			mapanon=0;
	int 			fpref=0;
	int error =0;
	int fd = uap->fd;
	int num_retries = 0;

	/*
	 * Note that for UNIX03 conformance, there is additional parameter checking for
	 * mmap() system call in libsyscall prior to entering the kernel.  The sanity 
	 * checks and argument validation done in this function are not the only places
	 * one can get returned errnos.
	 */

	user_map = current_map();
	user_addr = (vm_map_offset_t)uap->addr;
	user_size = (vm_map_size_t) uap->len;

	AUDIT_ARG(addr, user_addr);
	AUDIT_ARG(len, user_size);
	AUDIT_ARG(fd, uap->fd);

	prot = (uap->prot & VM_PROT_ALL);
#if 3777787
	/*
	 * Since the hardware currently does not support writing without
	 * read-before-write, or execution-without-read, if the request is
	 * for write or execute access, we must imply read access as well;
	 * otherwise programs expecting this to work will fail to operate.
	 */
	if (prot & (VM_PROT_EXECUTE | VM_PROT_WRITE))
		prot |= VM_PROT_READ;
#endif	/* radar 3777787 */

	flags = uap->flags;
	vp = NULLVP;

	/*
	 * The vm code does not have prototypes & compiler doesn't do the'
	 * the right thing when you cast 64bit value and pass it in function 
	 * call. So here it is.
	 */
	file_pos = (vm_object_offset_t)uap->pos;


	/* make sure mapping fits into numeric range etc */
	if (file_pos + user_size > (vm_object_offset_t)-PAGE_SIZE_64)
		return (EINVAL);

	/*
	 * Align the file position to a page boundary,
	 * and save its page offset component.
	 */
	pageoff = (file_pos & vm_map_page_mask(user_map));
	file_pos -= (vm_object_offset_t)pageoff;


	/* Adjust size for rounding (on both ends). */
	user_size += pageoff;	/* low end... */
	user_size = vm_map_round_page(user_size,	
				      vm_map_page_mask(user_map)); /* hi end */

	if (flags & MAP_JIT) {
		if ((flags & MAP_FIXED) ||
		    (flags & MAP_SHARED) ||
		    !(flags & MAP_ANON) ||
		    (flags & MAP_RESILIENT_CODESIGN) ||
		    (flags & MAP_RESILIENT_MEDIA)) {
			return EINVAL;
		}
	}

	if ((flags & MAP_RESILIENT_CODESIGN) ||
	    (flags & MAP_RESILIENT_MEDIA)) {
		if ((flags & MAP_ANON) ||
		    (flags & MAP_JIT)) {
			return EINVAL;
		}
		if (prot & (VM_PROT_WRITE | VM_PROT_EXECUTE)) {
			return EPERM;
		}
	}

	/*
	 * Check for illegal addresses.  Watch out for address wrap... Note
	 * that VM_*_ADDRESS are not constants due to casts (argh).
	 */
	if (flags & MAP_FIXED) {
		/*
		 * The specified address must have the same remainder
		 * as the file offset taken modulo PAGE_SIZE, so it
		 * should be aligned after adjustment by pageoff.
		 */
		user_addr -= pageoff;
		if (user_addr & vm_map_page_mask(user_map))
			return (EINVAL);
	}
#ifdef notyet
	/* DO not have apis to get this info, need to wait till then*/
	/*
	 * XXX for non-fixed mappings where no hint is provided or
	 * the hint would fall in the potential heap space,
	 * place it after the end of the largest possible heap.
	 *
	 * There should really be a pmap call to determine a reasonable
	 * location.
	 */
	else if (addr < vm_map_round_page(p->p_vmspace->vm_daddr + MAXDSIZ,
					  vm_map_page_mask(user_map)))
		addr = vm_map_round_page(p->p_vmspace->vm_daddr + MAXDSIZ,
					 vm_map_page_mask(user_map));

#endif

	alloc_flags = 0;

	if (flags & MAP_ANON) {

		maxprot = VM_PROT_ALL;
#if CONFIG_MACF
		/*
		 * Entitlement check.
		 */
		error = mac_proc_check_map_anon(p, user_addr, user_size, prot, flags, &maxprot);
		if (error) {
			return EINVAL;
		}		
#endif /* MAC */

		/*
		 * Mapping blank space is trivial.  Use positive fds as the alias
		 * value for memory tracking. 
		 */
		if (fd != -1) {
			/*
			 * Use "fd" to pass (some) Mach VM allocation flags,
			 * (see the VM_FLAGS_* definitions).
			 */
			alloc_flags = fd & (VM_FLAGS_ALIAS_MASK |
					    VM_FLAGS_SUPERPAGE_MASK |
					    VM_FLAGS_PURGABLE |
					    VM_FLAGS_4GB_CHUNK);
			if (alloc_flags != fd) {
				/* reject if there are any extra flags */
				return EINVAL;
			}
			VM_GET_FLAGS_ALIAS(alloc_flags, tag);
			alloc_flags &= ~VM_FLAGS_ALIAS_MASK;
		}
			
		handle = NULL;
		file_pos = 0;
		mapanon = 1;
	} else {
		struct vnode_attr va;
		vfs_context_t ctx = vfs_context_current();

		if (flags & MAP_JIT)
			return EINVAL;

		/*
		 * Mapping file, get fp for validation. Obtain vnode and make
		 * sure it is of appropriate type.
		 */
		err = fp_lookup(p, fd, &fp, 0);
		if (err)
			return(err);
		fpref = 1;
		switch (FILEGLOB_DTYPE(fp->f_fglob)) {
		case DTYPE_PSXSHM:
			uap->addr = (user_addr_t)user_addr;
			uap->len = (user_size_t)user_size;
			uap->prot = prot;
			uap->flags = flags;
			uap->pos = file_pos;
			error = pshm_mmap(p, uap, retval, fp, (off_t)pageoff);
			goto bad;
		case DTYPE_VNODE:
			break;
		default:
			error = EINVAL;
			goto bad;
		}
		vp = (struct vnode *)fp->f_fglob->fg_data;
		error = vnode_getwithref(vp);
		if(error != 0)
			goto bad;

		if (vp->v_type != VREG && vp->v_type != VCHR) {
			(void)vnode_put(vp);
			error = EINVAL;
			goto bad;
		}

		AUDIT_ARG(vnpath, vp, ARG_VNODE1);
		
		/*
		 * POSIX: mmap needs to update access time for mapped files
		 */
		if ((vnode_vfsvisflags(vp) & MNT_NOATIME) == 0) {
			VATTR_INIT(&va);
			nanotime(&va.va_access_time);
			VATTR_SET_ACTIVE(&va, va_access_time);
			vnode_setattr(vp, &va, ctx);
		}

		/*
		 * XXX hack to handle use of /dev/zero to map anon memory (ala
		 * SunOS).
		 */
		if (vp->v_type == VCHR || vp->v_type == VSTR) {
			(void)vnode_put(vp);
			error = ENODEV;
			goto bad;
		} else {
			/*
			 * Ensure that file and memory protections are
			 * compatible.  Note that we only worry about
			 * writability if mapping is shared; in this case,
			 * current and max prot are dictated by the open file.
			 * XXX use the vnode instead?  Problem is: what
			 * credentials do we use for determination? What if
			 * proc does a setuid?
			 */
			maxprot = VM_PROT_EXECUTE;	/* ??? */
			if (fp->f_fglob->fg_flag & FREAD)
				maxprot |= VM_PROT_READ;
			else if (prot & PROT_READ) {
				(void)vnode_put(vp);
				error = EACCES;
				goto bad;
			}
			/*
			 * If we are sharing potential changes (either via
			 * MAP_SHARED or via the implicit sharing of character
			 * device mappings), and we are trying to get write
			 * permission although we opened it without asking
			 * for it, bail out. 
			 */

			if ((flags & MAP_SHARED) != 0) {
				if ((fp->f_fglob->fg_flag & FWRITE) != 0 &&
				    /*
				     * Do not allow writable mappings of 
				     * swap files (see vm_swapfile_pager.c).
				     */
				    !vnode_isswap(vp)) {
 					/*
 					 * check for write access
 					 *
 					 * Note that we already made this check when granting FWRITE
 					 * against the file, so it seems redundant here.
 					 */
 					error = vnode_authorize(vp, NULL, KAUTH_VNODE_CHECKIMMUTABLE, ctx);
 
 					/* if not granted for any reason, but we wanted it, bad */
 					if ((prot & PROT_WRITE) && (error != 0)) {
 						vnode_put(vp);
  						goto bad;
  					}
 
 					/* if writable, remember */
 					if (error == 0)
  						maxprot |= VM_PROT_WRITE;

				} else if ((prot & PROT_WRITE) != 0) {
					(void)vnode_put(vp);
					error = EACCES;
					goto bad;
				}
			} else
				maxprot |= VM_PROT_WRITE;

			handle = (void *)vp;
#if CONFIG_MACF
			error = mac_file_check_mmap(vfs_context_ucred(ctx),
			    fp->f_fglob, prot, flags, file_pos, &maxprot);
			if (error) {
				(void)vnode_put(vp);
				goto bad;
			}
#endif /* MAC */
		}
	}

	if (user_size == 0)  {
		if (!mapanon)
			(void)vnode_put(vp);
		error = 0;
		goto bad;
	}

	/*
	 *	We bend a little - round the start and end addresses
	 *	to the nearest page boundary.
	 */
	user_size = vm_map_round_page(user_size,
				      vm_map_page_mask(user_map));

	if (file_pos & vm_map_page_mask(user_map)) {
		if (!mapanon)
			(void)vnode_put(vp);
		error = EINVAL;
		goto bad;
	}

	if ((flags & MAP_FIXED) == 0) {
		alloc_flags |= VM_FLAGS_ANYWHERE;
		user_addr = vm_map_round_page(user_addr,
					      vm_map_page_mask(user_map));
	} else {
		if (user_addr != vm_map_trunc_page(user_addr,
						   vm_map_page_mask(user_map))) {
		        if (!mapanon)
			        (void)vnode_put(vp);
			error = EINVAL;
			goto bad;
		}
		/*
		 * mmap(MAP_FIXED) will replace any existing mappings in the
		 * specified range, if the new mapping is successful.
		 * If we just deallocate the specified address range here,
		 * another thread might jump in and allocate memory in that
		 * range before we get a chance to establish the new mapping,
		 * and we won't have a chance to restore the old mappings.
		 * So we use VM_FLAGS_OVERWRITE to let Mach VM know that it
		 * has to deallocate the existing mappings and establish the
		 * new ones atomically.
		 */
		alloc_flags |= VM_FLAGS_FIXED | VM_FLAGS_OVERWRITE;
	}

	if (flags & MAP_NOCACHE)
		alloc_flags |= VM_FLAGS_NO_CACHE;

	if (flags & MAP_JIT) {
		vmk_flags.vmkf_map_jit = TRUE;
	}

	if (flags & MAP_RESILIENT_CODESIGN) {
		alloc_flags |= VM_FLAGS_RESILIENT_CODESIGN;
	}

	/*
	 * Lookup/allocate object.
	 */
	if (handle == NULL) {
		control = NULL;
#ifdef notyet
/* Hmm .. */
#if defined(VM_PROT_READ_IS_EXEC)
		if (prot & VM_PROT_READ)
			prot |= VM_PROT_EXECUTE;
		if (maxprot & VM_PROT_READ)
			maxprot |= VM_PROT_EXECUTE;
#endif
#endif

#if 3777787
		if (prot & (VM_PROT_EXECUTE | VM_PROT_WRITE))
			prot |= VM_PROT_READ;
		if (maxprot & (VM_PROT_EXECUTE | VM_PROT_WRITE))
			maxprot |= VM_PROT_READ;
#endif	/* radar 3777787 */
map_anon_retry:
		result = vm_map_enter_mem_object(user_map,
						 &user_addr, user_size,
						 0, alloc_flags, vmk_flags,
						 tag,
						 IPC_PORT_NULL, 0, FALSE,
						 prot, maxprot,
						 (flags & MAP_SHARED) ?
						 VM_INHERIT_SHARE : 
						 VM_INHERIT_DEFAULT);

		/* If a non-binding address was specified for this anonymous
		 * mapping, retry the mapping with a zero base
		 * in the event the mapping operation failed due to
		 * lack of space between the address and the map's maximum.
		 */
		if ((result == KERN_NO_SPACE) && ((flags & MAP_FIXED) == 0) && user_addr && (num_retries++ == 0)) {
			user_addr = vm_map_page_size(user_map);
			goto map_anon_retry;
		}
	} else {
		if (vnode_isswap(vp)) {
			/*
			 * Map swap files with a special pager
			 * that returns obfuscated contents.
			 */
			control = NULL;
			pager = swapfile_pager_setup(vp);
			if (pager != MEMORY_OBJECT_NULL) {
				control = swapfile_pager_control(pager);
			}
		} else {
			control = ubc_getobject(vp, UBC_FLAGS_NONE);
		}
		
		if (control == NULL) {
			(void)vnode_put(vp);
			error = ENOMEM;
			goto bad;
		}

		/*
		 *  Set credentials:
		 *	FIXME: if we're writing the file we need a way to
		 *      ensure that someone doesn't replace our R/W creds
		 * 	with ones that only work for read.
		 */

		ubc_setthreadcred(vp, p, current_thread());
		docow = FALSE;
		if ((flags & (MAP_ANON|MAP_SHARED)) == 0) {
			docow = TRUE;
		}

#ifdef notyet
/* Hmm .. */
#if defined(VM_PROT_READ_IS_EXEC)
		if (prot & VM_PROT_READ)
			prot |= VM_PROT_EXECUTE;
		if (maxprot & VM_PROT_READ)
			maxprot |= VM_PROT_EXECUTE;
#endif
#endif /* notyet */

#if 3777787
		if (prot & (VM_PROT_EXECUTE | VM_PROT_WRITE))
			prot |= VM_PROT_READ;
		if (maxprot & (VM_PROT_EXECUTE | VM_PROT_WRITE))
			maxprot |= VM_PROT_READ;
#endif	/* radar 3777787 */

map_file_retry:
		if ((flags & MAP_RESILIENT_CODESIGN) ||
		    (flags & MAP_RESILIENT_MEDIA)) {
			if (prot & (VM_PROT_WRITE | VM_PROT_EXECUTE)) {
				assert(!mapanon);
				vnode_put(vp);
				error = EPERM;
				goto bad;
			}
			/* strictly limit access to "prot" */
			maxprot &= prot;
		}

		vm_object_offset_t end_pos = 0;
		if (os_add_overflow(user_size, file_pos, &end_pos)) {
			vnode_put(vp);
			error = EINVAL;
			goto bad;
		}

		result = vm_map_enter_mem_object_control(user_map,
						 &user_addr, user_size,
						 0, alloc_flags, vmk_flags,
						 tag,
						 control, file_pos,
						 docow, prot, maxprot, 
						 (flags & MAP_SHARED) ?
						 VM_INHERIT_SHARE : 
						 VM_INHERIT_DEFAULT);

		/* If a non-binding address was specified for this file backed
		 * mapping, retry the mapping with a zero base
		 * in the event the mapping operation failed due to
		 * lack of space between the address and the map's maximum.
		 */
		if ((result == KERN_NO_SPACE) && ((flags & MAP_FIXED) == 0) && user_addr && (num_retries++ == 0)) {
			user_addr = vm_map_page_size(user_map);
			goto map_file_retry;
		}
	}

	if (!mapanon) {
		(void)vnode_put(vp);
	}

	switch (result) {
	case KERN_SUCCESS:
		*retval = user_addr + pageoff;
		error = 0;
		break;
	case KERN_INVALID_ADDRESS:
	case KERN_NO_SPACE:
		error =  ENOMEM;
		break;
	case KERN_PROTECTION_FAILURE:
		error =  EACCES;
		break;
	default:
		error =  EINVAL;
		break;
	}
bad:
	if (pager != MEMORY_OBJECT_NULL) {
		/*
		 * Release the reference on the pager.
		 * If the mapping was successful, it now holds
		 * an extra reference.
		 */
		memory_object_deallocate(pager);
	}
	if (fpref)
		fp_drop(p, fd, fp, 0);

	KERNEL_DEBUG_CONSTANT((BSDDBG_CODE(DBG_BSD_SC_EXTENDED_INFO, SYS_mmap) | DBG_FUNC_NONE), fd, (uint32_t)(*retval), (uint32_t)user_size, error, 0);
#ifndef	CONFIG_EMBEDDED
	KERNEL_DEBUG_CONSTANT((BSDDBG_CODE(DBG_BSD_SC_EXTENDED_INFO2, SYS_mmap) | DBG_FUNC_NONE), (uint32_t)(*retval >> 32), (uint32_t)(user_size >> 32),
			      (uint32_t)(file_pos >> 32), (uint32_t)file_pos, 0);
#endif
	return(error);
}