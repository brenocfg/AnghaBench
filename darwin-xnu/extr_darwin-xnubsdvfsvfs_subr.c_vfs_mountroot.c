#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
struct vfstable {int (* vfc_mountroot ) (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ;char* vfc_name; int /*<<< orphan*/  vfc_vfsflags; struct vfstable* vfc_next; } ;
struct TYPE_17__ {int* capabilities; int* valid; } ;
struct vfs_attr {TYPE_3__ f_capabilities; } ;
typedef  TYPE_4__* mount_t ;
struct TYPE_18__ {int mnt_ioflags; int mnt_kern_flag; TYPE_2__* mnt_vtable; TYPE_1__* mnt_devvp; } ;
struct TYPE_16__ {int vfc_vfsflags; } ;
struct TYPE_15__ {int /*<<< orphan*/  v_specflags; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int DBG_MOUNTROOT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KDBG_RELEASE (int,...) ; 
 int MNTK_DIR_HARDLINKS ; 
 int MNTK_EXTENDED_ATTRS ; 
 int MNTK_PATH_FROM_ID ; 
 int MNTK_UNMOUNT_PREFLIGHT ; 
 int MNTK_VIRTUALDEV ; 
 int MNT_IOFLAGS_FUSION_DRIVE ; 
 int /*<<< orphan*/  SI_MOUNTEDON ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VFC_VFSCANMOUNTROOT ; 
 int VFC_VFSNATIVEXATTR ; 
 int VFC_VFSPREFLIGHT ; 
 int /*<<< orphan*/  VFSATTR_INIT (struct vfs_attr*) ; 
 scalar_t__ VFSATTR_IS_SUPPORTED (struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFSATTR_WANTED (struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int VFS_MOUNT (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFS_START (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t VOL_CAPABILITIES_FORMAT ; 
 size_t VOL_CAPABILITIES_INTERFACES ; 
 int VOL_CAP_FMT_DIR_HARDLINKS ; 
 int VOL_CAP_FMT_PATH_FROM_ID ; 
 int VOL_CAP_INT_EXTENDED_ATTR ; 
 int bdevvp (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ disk_conditioner_mount_is_ssd (TYPE_4__*) ; 
 int /*<<< orphan*/  f_capabilities ; 
 int /*<<< orphan*/  mount_list_add (TYPE_4__*) ; 
 int mountroot () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  root_is_CF_drive ; 
 int /*<<< orphan*/  rootdev ; 
 scalar_t__ rootvp ; 
 int stub1 () ; 
 int stub2 (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_progress_setdiskspeed (int) ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 
 scalar_t__ vfs_getattr (TYPE_4__*,struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_init_io_attributes (scalar_t__,TYPE_4__*) ; 
 TYPE_4__* vfs_rootmountalloc_internal (struct vfstable*,char*) ; 
 int /*<<< orphan*/  vfs_rootmountfailed (TYPE_4__*) ; 
 int /*<<< orphan*/  vfs_unbusy (TYPE_4__*) ; 
 struct vfstable* vfsconf ; 
 int /*<<< orphan*/  vnode_getwithref (scalar_t__) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 
 int /*<<< orphan*/  vnode_rele (scalar_t__) ; 

int
vfs_mountroot(void)
{
#if CONFIG_MACF
	struct vnode *vp;
#endif
	struct vfstable *vfsp;
	vfs_context_t ctx = vfs_context_kernel();
	struct vfs_attr	vfsattr;
	int	error;
	mount_t mp;
	vnode_t	bdevvp_rootvp;

	KDBG_RELEASE(DBG_MOUNTROOT | DBG_FUNC_START);
	if (mountroot != NULL) {
		/*
		 * used for netboot which follows a different set of rules
		 */
		error = (*mountroot)();

		KDBG_RELEASE(DBG_MOUNTROOT | DBG_FUNC_END, error, 0);
		return (error);
	}
	if ((error = bdevvp(rootdev, &rootvp))) {
		printf("vfs_mountroot: can't setup bdevvp\n");

		KDBG_RELEASE(DBG_MOUNTROOT | DBG_FUNC_END, error, 1);
		return (error);
	}
	/*
	 * 4951998 - code we call in vfc_mountroot may replace rootvp 
	 * so keep a local copy for some house keeping.
	 */
	bdevvp_rootvp = rootvp;

	for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next) {
		if (vfsp->vfc_mountroot == NULL
			&& !ISSET(vfsp->vfc_vfsflags, VFC_VFSCANMOUNTROOT)) {
			continue;
		}

		mp = vfs_rootmountalloc_internal(vfsp, "root_device");
		mp->mnt_devvp = rootvp;

		if (vfsp->vfc_mountroot)
			error = (*vfsp->vfc_mountroot)(mp, rootvp, ctx);
		else
			error = VFS_MOUNT(mp, rootvp, 0, ctx);

		if (!error) {
			if ( bdevvp_rootvp != rootvp ) {
				/*
				 * rootvp changed...
				 *   bump the iocount and fix up mnt_devvp for the
				 *   new rootvp (it will already have a usecount taken)...
				 *   drop the iocount and the usecount on the orignal
				 *   since we are no longer going to use it...
				 */
				vnode_getwithref(rootvp);
				mp->mnt_devvp = rootvp;

			        vnode_rele(bdevvp_rootvp);
			        vnode_put(bdevvp_rootvp);
			}
			mp->mnt_devvp->v_specflags |= SI_MOUNTEDON;

			vfs_unbusy(mp);

			mount_list_add(mp);

			/*
			 *   cache the IO attributes for the underlying physical media...
			 *   an error return indicates the underlying driver doesn't
			 *   support all the queries necessary... however, reasonable
			 *   defaults will have been set, so no reason to bail or care
			 */
			vfs_init_io_attributes(rootvp, mp);

			if (mp->mnt_ioflags & MNT_IOFLAGS_FUSION_DRIVE) {
				root_is_CF_drive = TRUE;
			}

			/*
			 * Shadow the VFC_VFSNATIVEXATTR flag to MNTK_EXTENDED_ATTRS.
			 */
			if (mp->mnt_vtable->vfc_vfsflags & VFC_VFSNATIVEXATTR) {
				mp->mnt_kern_flag |= MNTK_EXTENDED_ATTRS;
			}
			if (mp->mnt_vtable->vfc_vfsflags & VFC_VFSPREFLIGHT) {
				mp->mnt_kern_flag |= MNTK_UNMOUNT_PREFLIGHT;
			}

#if !CONFIG_EMBEDDED
			uint32_t speed;

			if (MNTK_VIRTUALDEV & mp->mnt_kern_flag)    speed = 128;
			else if (disk_conditioner_mount_is_ssd(mp)) speed = 7*256;
			else                                        speed = 256;
			vc_progress_setdiskspeed(speed);
#endif
			/*
			 * Probe root file system for additional features.
			 */
			(void)VFS_START(mp, 0, ctx);

			VFSATTR_INIT(&vfsattr);
			VFSATTR_WANTED(&vfsattr, f_capabilities);
			if (vfs_getattr(mp, &vfsattr, ctx) == 0 && 
			    VFSATTR_IS_SUPPORTED(&vfsattr, f_capabilities)) {
				if ((vfsattr.f_capabilities.capabilities[VOL_CAPABILITIES_INTERFACES] & VOL_CAP_INT_EXTENDED_ATTR) &&
				    (vfsattr.f_capabilities.valid[VOL_CAPABILITIES_INTERFACES] & VOL_CAP_INT_EXTENDED_ATTR)) {
					mp->mnt_kern_flag |= MNTK_EXTENDED_ATTRS;
				}
#if NAMEDSTREAMS
				if ((vfsattr.f_capabilities.capabilities[VOL_CAPABILITIES_INTERFACES] & VOL_CAP_INT_NAMEDSTREAMS) &&
				    (vfsattr.f_capabilities.valid[VOL_CAPABILITIES_INTERFACES] & VOL_CAP_INT_NAMEDSTREAMS)) {
					mp->mnt_kern_flag |= MNTK_NAMED_STREAMS;
				}
#endif
				if ((vfsattr.f_capabilities.capabilities[VOL_CAPABILITIES_FORMAT] & VOL_CAP_FMT_PATH_FROM_ID) &&
				    (vfsattr.f_capabilities.valid[VOL_CAPABILITIES_FORMAT] & VOL_CAP_FMT_PATH_FROM_ID)) {
					mp->mnt_kern_flag |= MNTK_PATH_FROM_ID;
				}

				if ((vfsattr.f_capabilities.capabilities[VOL_CAPABILITIES_FORMAT] & VOL_CAP_FMT_DIR_HARDLINKS) &&
					(vfsattr.f_capabilities.valid[VOL_CAPABILITIES_FORMAT] & VOL_CAP_FMT_DIR_HARDLINKS)) {
					mp->mnt_kern_flag |= MNTK_DIR_HARDLINKS;
				}
			}

			/*
			 * get rid of iocount reference returned
			 * by bdevvp (or picked up by us on the substitued
			 * rootvp)... it (or we) will have also taken
			 * a usecount reference which we want to keep
			 */
			vnode_put(rootvp);

#if CONFIG_MACF
			if ((vfs_flags(mp) & MNT_MULTILABEL) == 0) {
				KDBG_RELEASE(DBG_MOUNTROOT | DBG_FUNC_END, 0, 2);
				return (0);
			}

			error = VFS_ROOT(mp, &vp, ctx);
			if (error) {
				printf("%s() VFS_ROOT() returned %d\n",
				    __func__, error);
				dounmount(mp, MNT_FORCE, 0, ctx);
				goto fail;
			}
			error = vnode_label(mp, NULL, vp, NULL, 0, ctx);
			/*
			 * get rid of reference provided by VFS_ROOT
			 */
			vnode_put(vp);

			if (error) {
				printf("%s() vnode_label() returned %d\n",
				    __func__, error);
				dounmount(mp, MNT_FORCE, 0, ctx);
				goto fail;
			}
#endif
			KDBG_RELEASE(DBG_MOUNTROOT | DBG_FUNC_END, 0, 3);
			return (0);
		}
#if CONFIG_MACF
fail:
#endif
		vfs_rootmountfailed(mp);

		if (error != EINVAL)
			printf("%s_mountroot failed: %d\n", vfsp->vfc_name, error);
	}
	KDBG_RELEASE(DBG_MOUNTROOT | DBG_FUNC_END, error ? error : ENODEV, 4);
	return (ENODEV);
}