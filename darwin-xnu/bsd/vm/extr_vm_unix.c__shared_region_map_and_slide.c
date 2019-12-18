#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  size_t uint32_t ;
struct vnode_attr {scalar_t__ va_uid; int /*<<< orphan*/  va_access_time; } ;
struct vnode {scalar_t__ v_type; scalar_t__ v_mount; int /*<<< orphan*/  v_flag; int /*<<< orphan*/  v_name; } ;
struct vm_shared_region {int dummy; } ;
struct shared_file_mapping_np {int sfm_init_prot; int /*<<< orphan*/  sfm_max_prot; int /*<<< orphan*/  sfm_file_offset; int /*<<< orphan*/  sfm_size; int /*<<< orphan*/  sfm_address; } ;
struct proc {int p_flag; int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_pid; TYPE_1__* p_fd; } ;
struct fileproc {TYPE_2__* f_fglob; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  memory_object_size_t ;
typedef  scalar_t__ memory_object_control_t ;
typedef  int kern_return_t ;
struct TYPE_5__ {int fg_flag; scalar_t__ fg_data; } ;
struct TYPE_4__ {struct vnode* fd_rdir; } ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 scalar_t__ FILEGLOB_DTYPE (TYPE_2__*) ; 
 int FREAD ; 
#define  KERN_FAILURE 132 
#define  KERN_INVALID_ADDRESS 131 
#define  KERN_INVALID_ARGUMENT 130 
#define  KERN_NO_SPACE 129 
#define  KERN_PROTECTION_FAILURE 128 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  MAP_FILE ; 
 scalar_t__ MEMORY_OBJECT_CONTROL_NULL ; 
 int MNT_NOATIME ; 
 int /*<<< orphan*/  OSBitAndAtomic (size_t,int*) ; 
 int P_NOSHLIB ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  UBC_HOLDOBJECT ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct vnode*) ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int VM_PROT_ZF ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  VSHARED_DYLD ; 
 int /*<<< orphan*/  cs_system_enforcement () ; 
 int /*<<< orphan*/  current_task () ; 
 struct vnode* current_thread () ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_lookup (struct proc*,int,struct fileproc**,int /*<<< orphan*/ ) ; 
 int mac_file_check_mmap (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nanotime (int /*<<< orphan*/ *) ; 
 struct vnode* rootvnode ; 
 scalar_t__ scdir_enforce ; 
 int /*<<< orphan*/  scdir_path ; 
 scalar_t__ ubc_cs_is_range_codesigned (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ubc_getobject (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_access_time ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_shared_region_deallocate (struct vm_shared_region*) ; 
 int vm_shared_region_map_file (struct vm_shared_region*,size_t,struct shared_file_mapping_np*,scalar_t__,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vm_shared_region* vm_shared_region_trim_and_get (int /*<<< orphan*/ ) ; 
 int vnode_getattr (struct vnode*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int vnode_getwithref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_lock_spin (struct vnode*) ; 
 int vnode_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode**,int /*<<< orphan*/ ) ; 
 struct vnode* vnode_parent (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int /*<<< orphan*/  vnode_setattr (struct vnode*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int vnode_size (struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 
 int vnode_vfsvisflags (struct vnode*) ; 

int
_shared_region_map_and_slide(
	struct proc				*p,
	int					fd,
	uint32_t				mappings_count,
	struct shared_file_mapping_np		*mappings,
	uint32_t				slide,
	user_addr_t				slide_start,
	user_addr_t				slide_size)
{
	int				error;
	kern_return_t			kr;
	struct fileproc			*fp;
	struct vnode			*vp, *root_vp, *scdir_vp;
	struct vnode_attr		va;
	off_t				fs;
	memory_object_size_t		file_size;
#if CONFIG_MACF
	vm_prot_t			maxprot = VM_PROT_ALL;
#endif
	memory_object_control_t		file_control;
	struct vm_shared_region		*shared_region;
	uint32_t			i;

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: %p [%d(%s)] -> map\n",
		 (void *)VM_KERNEL_ADDRPERM(current_thread()),
		 p->p_pid, p->p_comm));

	shared_region = NULL;
	fp = NULL;
	vp = NULL;
	scdir_vp = NULL;

	/* get file structure from file descriptor */
	error = fp_lookup(p, fd, &fp, 0);
	if (error) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map: "
			 "fd=%d lookup failed (error=%d)\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm, fd, error));
		goto done;
	}

	/* make sure we're attempting to map a vnode */
	if (FILEGLOB_DTYPE(fp->f_fglob) != DTYPE_VNODE) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map: "
			 "fd=%d not a vnode (type=%d)\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm,
			 fd, FILEGLOB_DTYPE(fp->f_fglob)));
		error = EINVAL;
		goto done;
	}

	/* we need at least read permission on the file */
	if (! (fp->f_fglob->fg_flag & FREAD)) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map: "
			 "fd=%d not readable\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm, fd));
		error = EPERM;
		goto done;
	}

	/* get vnode from file structure */
	error = vnode_getwithref((vnode_t) fp->f_fglob->fg_data);
	if (error) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map: "
			 "fd=%d getwithref failed (error=%d)\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm, fd, error));
		goto done;
	}
	vp = (struct vnode *) fp->f_fglob->fg_data;

	/* make sure the vnode is a regular file */
	if (vp->v_type != VREG) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map(%p:'%s'): "
			 "not a file (type=%d)\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm,
			 (void *)VM_KERNEL_ADDRPERM(vp),
			 vp->v_name, vp->v_type));
		error = EINVAL;
		goto done;
	}

#if CONFIG_MACF
	/* pass in 0 for the offset argument because AMFI does not need the offset
		of the shared cache */
	error = mac_file_check_mmap(vfs_context_ucred(vfs_context_current()),
			fp->f_fglob, VM_PROT_ALL, MAP_FILE, 0, &maxprot);
	if (error) {
		goto done;
	}
#endif /* MAC */

	/* make sure vnode is on the process's root volume */
	root_vp = p->p_fd->fd_rdir;
	if (root_vp == NULL) {
		root_vp = rootvnode;
	} else {
		/*
		 * Chroot-ed processes can't use the shared_region.
		 */
		error = EINVAL;
		goto done;
	}

	if (vp->v_mount != root_vp->v_mount) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map(%p:'%s'): "
			 "not on process's root volume\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm,
			 (void *)VM_KERNEL_ADDRPERM(vp), vp->v_name));
		error = EPERM;
		goto done;
	}

	/* make sure vnode is owned by "root" */
	VATTR_INIT(&va);
	VATTR_WANTED(&va, va_uid);
	error = vnode_getattr(vp, &va, vfs_context_current());
	if (error) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map(%p:'%s'): "
			 "vnode_getattr(%p) failed (error=%d)\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm,
			 (void *)VM_KERNEL_ADDRPERM(vp), vp->v_name,
			 (void *)VM_KERNEL_ADDRPERM(vp), error));
		goto done;
	}
	if (va.va_uid != 0) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map(%p:'%s'): "
			 "owned by uid=%d instead of 0\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm,
			 (void *)VM_KERNEL_ADDRPERM(vp),
			 vp->v_name, va.va_uid));
		error = EPERM;
		goto done;
	}

	if (scdir_enforce) {
		/* get vnode for scdir_path */
		error = vnode_lookup(scdir_path, 0, &scdir_vp, vfs_context_current());
		if (error) {
			SHARED_REGION_TRACE_ERROR(
				("shared_region: %p [%d(%s)] map(%p:'%s'): "
				 "vnode_lookup(%s) failed (error=%d)\n",
				 (void *)VM_KERNEL_ADDRPERM(current_thread()),
				 p->p_pid, p->p_comm,
				 (void *)VM_KERNEL_ADDRPERM(vp), vp->v_name,
				 scdir_path, error));
			goto done;
		}

		/* ensure parent is scdir_vp */
		if (vnode_parent(vp) != scdir_vp) {
			SHARED_REGION_TRACE_ERROR(
				("shared_region: %p [%d(%s)] map(%p:'%s'): "
				 "shared cache file not in %s\n",
				 (void *)VM_KERNEL_ADDRPERM(current_thread()),
				 p->p_pid, p->p_comm,
				 (void *)VM_KERNEL_ADDRPERM(vp),
				 vp->v_name, scdir_path));
			error = EPERM;
			goto done;
		}
	}

	/* get vnode size */
	error = vnode_size(vp, &fs, vfs_context_current());
	if (error) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map(%p:'%s'): "
			 "vnode_size(%p) failed (error=%d)\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm,
			 (void *)VM_KERNEL_ADDRPERM(vp), vp->v_name,
			 (void *)VM_KERNEL_ADDRPERM(vp), error));
		goto done;
	}
	file_size = fs;

	/* get the file's memory object handle */
	file_control = ubc_getobject(vp, UBC_HOLDOBJECT);
	if (file_control == MEMORY_OBJECT_CONTROL_NULL) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map(%p:'%s'): "
			 "no memory object\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm,
			 (void *)VM_KERNEL_ADDRPERM(vp), vp->v_name));
		error = EINVAL;
		goto done;
	}

	/* check that the mappings are properly covered by code signatures */
	if (!cs_system_enforcement()) {
		/* code signing is not enforced: no need to check */
	} else for (i = 0; i < mappings_count; i++) {
		if (mappings[i].sfm_init_prot & VM_PROT_ZF) {
			/* zero-filled mapping: not backed by the file */
			continue;
		}
		if (ubc_cs_is_range_codesigned(vp,
					       mappings[i].sfm_file_offset,
					       mappings[i].sfm_size)) {
			/* this mapping is fully covered by code signatures */
			continue;
		}
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map(%p:'%s'): "
			 "mapping #%d/%d [0x%llx:0x%llx:0x%llx:0x%x:0x%x] "
			 "is not code-signed\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm,
			 (void *)VM_KERNEL_ADDRPERM(vp), vp->v_name,
			 i, mappings_count,
			 mappings[i].sfm_address,
			 mappings[i].sfm_size,
			 mappings[i].sfm_file_offset,
			 mappings[i].sfm_max_prot,
			 mappings[i].sfm_init_prot));
		error = EINVAL;
		goto done;
	}

	/* get the process's shared region (setup in vm_map_exec()) */
	shared_region = vm_shared_region_trim_and_get(current_task());
	if (shared_region == NULL) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map(%p:'%s'): "
			 "no shared region\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm,
			 (void *)VM_KERNEL_ADDRPERM(vp), vp->v_name));
		error = EINVAL;
		goto done;
	}

	/* map the file into that shared region's submap */
	kr = vm_shared_region_map_file(shared_region,
				       mappings_count,
				       mappings,
				       file_control,
				       file_size,
				       (void *) p->p_fd->fd_rdir,
				       slide,
				       slide_start,
				       slide_size);
	if (kr != KERN_SUCCESS) {
		SHARED_REGION_TRACE_ERROR(
			("shared_region: %p [%d(%s)] map(%p:'%s'): "
			 "vm_shared_region_map_file() failed kr=0x%x\n",
			 (void *)VM_KERNEL_ADDRPERM(current_thread()),
			 p->p_pid, p->p_comm,
			 (void *)VM_KERNEL_ADDRPERM(vp), vp->v_name, kr));
		switch (kr) {
		case KERN_INVALID_ADDRESS:
			error = EFAULT;
			break;
		case KERN_PROTECTION_FAILURE:
			error = EPERM;
			break;
		case KERN_NO_SPACE:
			error = ENOMEM;
			break;
		case KERN_FAILURE:
		case KERN_INVALID_ARGUMENT:
		default:
			error = EINVAL;
			break;
		}
		goto done;
	}

	error = 0;

	vnode_lock_spin(vp);

	vp->v_flag |= VSHARED_DYLD;

	vnode_unlock(vp);

	/* update the vnode's access time */
	if (! (vnode_vfsvisflags(vp) & MNT_NOATIME)) {
		VATTR_INIT(&va);
		nanotime(&va.va_access_time);
		VATTR_SET_ACTIVE(&va, va_access_time);
		vnode_setattr(vp, &va, vfs_context_current());
	}

	if (p->p_flag & P_NOSHLIB) {
		/* signal that this process is now using split libraries */
		OSBitAndAtomic(~((uint32_t)P_NOSHLIB), &p->p_flag);
	}

done:
	if (vp != NULL) {
		/*
		 * release the vnode...
		 * ubc_map() still holds it for us in the non-error case
		 */
		(void) vnode_put(vp);
		vp = NULL;
	}
	if (fp != NULL) {
		/* release the file descriptor */
		fp_drop(p, fd, fp, 0);
		fp = NULL;
	}
	if (scdir_vp != NULL) {
		(void)vnode_put(scdir_vp);
		scdir_vp = NULL;
	}

	if (shared_region != NULL) {
		vm_shared_region_deallocate(shared_region);
	}

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: %p [%d(%s)] <- map\n",
		 (void *)VM_KERNEL_ADDRPERM(current_thread()),
		 p->p_pid, p->p_comm));

	return error;
}