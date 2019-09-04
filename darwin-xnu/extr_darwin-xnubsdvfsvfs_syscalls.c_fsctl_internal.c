#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_23__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_13__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  scalar_t__ user_addr_t ;
struct TYPE_28__ {int num_entries; int max_width; scalar_t__ strings; } ;
typedef  TYPE_2__ user64_package_ext_info ;
struct TYPE_29__ {int num_entries; int max_width; int /*<<< orphan*/  strings; } ;
typedef  TYPE_3__ user32_package_ext_info ;
typedef  int uint32_t ;
typedef  int u_long ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  stkbuf ;
typedef  TYPE_4__* proc_t ;
typedef  TYPE_5__* mount_t ;
typedef  int /*<<< orphan*/  disk_conditioner_info ;
typedef  char* caddr_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_32__ {int /*<<< orphan*/  v_flag; } ;
struct TYPE_31__ {char* fstypename_override; int /*<<< orphan*/  mnt_kern_flag; } ;
struct TYPE_30__ {int /*<<< orphan*/  p_acflag; } ;
struct TYPE_27__ {int /*<<< orphan*/  p_acflag; } ;
struct TYPE_26__ {int v_id; TYPE_5__* v_mount; } ;
struct TYPE_25__ {int token; TYPE_6__* vp; int /*<<< orphan*/  flags; int /*<<< orphan*/  vid; int /*<<< orphan*/ * arg; int /*<<< orphan*/  op; } ;

/* Variables and functions */
#define  APFSIOC_REVERT_TO_SNAPSHOT 164 
 scalar_t__ CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
#define  DISK_CONDITIONER_IOC_GET 163 
#define  DISK_CONDITIONER_IOC_SET 162 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
#define  FIOPINSWAP 161 
 int FSCTL_SYNC_FULLSYNC ; 
 int FSCTL_SYNC_WAIT ; 
#define  FSIOC_FIOSEEKDATA 160 
#define  FSIOC_FIOSEEKHOLE 159 
#define  FSIOC_NAMESPACE_ALLOW_DMG_SNAPSHOT_EVENTS 158 
#define  FSIOC_NAMESPACE_HANDLER_CANCEL 157 
#define  FSIOC_NAMESPACE_HANDLER_GET 156 
#define  FSIOC_NAMESPACE_HANDLER_SET_SNAPSHOT_TIME 155 
#define  FSIOC_NAMESPACE_HANDLER_UNBLOCK 154 
#define  FSIOC_NAMESPACE_HANDLER_UPDATE 153 
#define  FSIOC_OLD_SNAPSHOT_HANDLER_GET 152 
#define  FSIOC_ROUTEFS_SETROUTEID 151 
#define  FSIOC_SET_FSTYPENAME_OVERRIDE 150 
#define  FSIOC_SET_PACKAGE_EXTS 149 
#define  FSIOC_SNAPSHOT_HANDLER_GET_EXT 148 
#define  FSIOC_SYNC_VOLUME 147 
#define  F_BARRIERFSYNC 146 
#define  F_CHKCLEAN 145 
#define  F_FREEZE_FS 144 
#define  F_FULLFSYNC 143 
#define  F_GETDEFAULTPROTLEVEL 142 
#define  F_GETPATH_MTMINFO 141 
#define  F_GETPROTECTIONLEVEL 140 
#define  F_MAKECOMPRESSED 139 
#define  F_PUNCHHOLE 138 
#define  F_RDADVISE 137 
#define  F_SETBACKINGSTORE 136 
#define  F_SETIOTYPE 135 
#define  F_SETSTATICCONTENT 134 
#define  F_SET_GREEDY_MODE 133 
#define  F_THAW_FS 132 
#define  F_TRANSCODEKEY 131 
#define  F_TRIM_ACTIVE_FILE 130 
#define  HFS_GET_BOOT_INFO 129 
#define  HFS_SET_BOOT_INFO 128 
 int IOCPARM_LEN (int) ; 
 int IOCPARM_MAX ; 
 int IOC_IN ; 
 int IOC_OUT ; 
 int IOC_VOID ; 
 int MAX_NSPACE_ITEMS ; 
 int /*<<< orphan*/  MFSTYPENAMELEN ; 
 int /*<<< orphan*/  MNTK_AUTH_OPAQUE ; 
 int /*<<< orphan*/  MNTK_EXTENDED_SECURITY ; 
 int /*<<< orphan*/  MNTK_TYPENAME_OVERRIDE ; 
 int /*<<< orphan*/  NSPACE_HANDLER_NSPACE ; 
 int /*<<< orphan*/  NSPACE_HANDLER_SNAPSHOT ; 
 int /*<<< orphan*/  NSPACE_ITEM_CANCELLED ; 
 int /*<<< orphan*/  NSPACE_ITEM_DONE ; 
 int /*<<< orphan*/  NSPACE_ITEM_PROCESSING ; 
 int /*<<< orphan*/  NSPACE_ITEM_RESET_TIMER ; 
 int /*<<< orphan*/  PRIV_PACKAGE_EXTENSIONS ; 
 int /*<<< orphan*/  VNEEDSSNAPSHOT ; 
 int VNOP_IOCTL (TYPE_1__*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int copyin (scalar_t__,char*,int) ; 
 int copyout (char*,scalar_t__,int) ; 
 TYPE_23__* current_proc () ; 
 int disk_conditioner_get_info (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int disk_conditioner_set_info (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int fsctl_bogus_command_compat (int) ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kfree (char*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mount_iterdrop (TYPE_5__*) ; 
 int mount_iterref (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  mount_unlock (TYPE_5__*) ; 
 int nspace_allow_virtual_devs ; 
 int /*<<< orphan*/  nspace_handler_lock ; 
 int /*<<< orphan*/  nspace_is_special_process (TYPE_4__*) ; 
 char nspace_item_idx ; 
 TYPE_13__* nspace_items ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int priv_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ proc_is64bit (TYPE_4__*) ; 
 int process_namespace_fsctl (int /*<<< orphan*/ ,scalar_t__,int,char*) ; 
 int set_package_extensions_table (scalar_t__,int,int) ; 
 int snapshot_timestamp ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int suser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_callback (TYPE_5__*,int*) ; 
 int /*<<< orphan*/  vfs_isrdonly (TYPE_5__*) ; 
 int vnode_getwithvid (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_6__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_6__*) ; 
 int /*<<< orphan*/  wakeup (char*) ; 

__attribute__((used)) static int
fsctl_internal(proc_t p, vnode_t *arg_vp, u_long cmd, user_addr_t udata, u_long options, vfs_context_t ctx)
{
	int error=0;
	boolean_t is64bit;
	u_int size;
#define STK_PARAMS 128
	char stkbuf[STK_PARAMS] = {0};
	caddr_t data, memp;
	vnode_t vp = *arg_vp;

	cmd = fsctl_bogus_command_compat(cmd);

	size = IOCPARM_LEN(cmd);
	if (size > IOCPARM_MAX) return (EINVAL);

	is64bit = proc_is64bit(p);

	memp = NULL;

	if (size > sizeof (stkbuf)) {
		if ((memp = (caddr_t)kalloc(size)) == 0) return ENOMEM;
		data = memp;
	} else {
		data = &stkbuf[0];
	};

	if (cmd & IOC_IN) {
		if (size) {
			error = copyin(udata, data, size);
			if (error) {
				if (memp) {
					kfree (memp, size);
				}
				return error;
			}
		} else {
			if (is64bit) {
				*(user_addr_t *)data = udata;
			}
			else {
				*(uint32_t *)data = (uint32_t)udata;
			}
		};
	} else if ((cmd & IOC_OUT) && size) {
		/*
		 * Zero the buffer so the user always
		 * gets back something deterministic.
		 */
		bzero(data, size);
	} else if (cmd & IOC_VOID) {
		if (is64bit) {
			*(user_addr_t *)data = udata;
		}
		else {
			*(uint32_t *)data = (uint32_t)udata;
		}
	}

	/* Check to see if it's a generic command */
	switch (cmd) {

		case FSIOC_SYNC_VOLUME: {
			mount_t mp = vp->v_mount;
			int arg = *(uint32_t*)data;

			/* record vid of vp so we can drop it below. */
			uint32_t vvid = vp->v_id;

			/*
			 * Then grab mount_iterref so that we can release the vnode.
			 * Without this, a thread may call vnode_iterate_prepare then
			 * get into a deadlock because we've never released the root vp
			 */
			error = mount_iterref (mp, 0);
			if (error)  {
				break;
			}
			vnode_put(vp);

			/* issue the sync for this volume */
			(void)sync_callback(mp, (arg & FSCTL_SYNC_WAIT) ? &arg : NULL);

			/*
			 * Then release the mount_iterref once we're done syncing; it's not
			 * needed for the VNOP_IOCTL below
			 */
			mount_iterdrop(mp);

			if (arg & FSCTL_SYNC_FULLSYNC) {
				/* re-obtain vnode iocount on the root vp, if possible */
				error = vnode_getwithvid (vp, vvid);
				if (error == 0) {
					error = VNOP_IOCTL(vp, F_FULLFSYNC, (caddr_t)NULL, 0, ctx);
					vnode_put (vp);
				}
			}
			/* mark the argument VP as having been released */
			*arg_vp = NULL;
		}
		break;

		case FSIOC_ROUTEFS_SETROUTEID: {
#if ROUTEFS
			char routepath[MAXPATHLEN];
			size_t len = 0;

			if ((error = suser(kauth_cred_get(), &(current_proc()->p_acflag)))) {
				break;
			}
			bzero(routepath, MAXPATHLEN);
			error = copyinstr(udata, &routepath[0], MAXPATHLEN, &len);
			if (error) {
				break;
			}
			error = routefs_kernel_mount(routepath);
			if (error) {
				break;
			}
#endif
		}
		break;

		case FSIOC_SET_PACKAGE_EXTS: {
			user_addr_t ext_strings;
			uint32_t    num_entries;
			uint32_t    max_width;

			if ((error = priv_check_cred(kauth_cred_get(), PRIV_PACKAGE_EXTENSIONS, 0)))
				break;

			if (   (is64bit && size != sizeof(user64_package_ext_info))
					|| (is64bit == 0 && size != sizeof(user32_package_ext_info))) {

				// either you're 64-bit and passed a 64-bit struct or
				// you're 32-bit and passed a 32-bit struct.  otherwise
				// it's not ok.
				error = EINVAL;
				break;
			}

			if (is64bit) {
				ext_strings = ((user64_package_ext_info *)data)->strings;
				num_entries = ((user64_package_ext_info *)data)->num_entries;
				max_width   = ((user64_package_ext_info *)data)->max_width;
			} else {
				ext_strings = CAST_USER_ADDR_T(((user32_package_ext_info *)data)->strings);
				num_entries = ((user32_package_ext_info *)data)->num_entries;
				max_width   = ((user32_package_ext_info *)data)->max_width;
			}
			error = set_package_extensions_table(ext_strings, num_entries, max_width);
		}
		break;

   		/* namespace handlers */
		case FSIOC_NAMESPACE_HANDLER_GET: {
			error = process_namespace_fsctl(NSPACE_HANDLER_NSPACE, is64bit, size, data);
		}
		break;

		/* Snapshot handlers */
		case FSIOC_OLD_SNAPSHOT_HANDLER_GET: {
			error = process_namespace_fsctl(NSPACE_HANDLER_SNAPSHOT, is64bit, size, data);
		}
		break;

		case FSIOC_SNAPSHOT_HANDLER_GET_EXT: {
			error = process_namespace_fsctl(NSPACE_HANDLER_SNAPSHOT, is64bit, size, data);
		}
		break;

		case FSIOC_NAMESPACE_HANDLER_UPDATE: {
			uint32_t token, val;
			int i;

			if ((error = suser(kauth_cred_get(), &(p->p_acflag)))) {
				break;
			}

			if (!nspace_is_special_process(p)) {
				error = EINVAL;
				break;
			}

			token = ((uint32_t *)data)[0];
			val   = ((uint32_t *)data)[1];

			lck_mtx_lock(&nspace_handler_lock);

			for(i=0; i < MAX_NSPACE_ITEMS; i++) {
				if (nspace_items[i].token == token) {
					break;  /* exit for loop, not case stmt */
				}
			}

			if (i >= MAX_NSPACE_ITEMS) {
				error = ENOENT;
			} else {
				//
				// if this bit is set, when resolve_nspace_item() times out
				// it will loop and go back to sleep.
				//
				nspace_items[i].flags |= NSPACE_ITEM_RESET_TIMER;
			}

			lck_mtx_unlock(&nspace_handler_lock);

			if (error) {
				printf("nspace-handler-update: did not find token %u\n", token);
			}
		}
		break;

		case FSIOC_NAMESPACE_HANDLER_UNBLOCK: {
			uint32_t token, val;
			int i;

			if ((error = suser(kauth_cred_get(), &(p->p_acflag)))) {
				break;
			}

			if (!nspace_is_special_process(p)) {
				error = EINVAL;
				break;
			}

			token = ((uint32_t *)data)[0];
			val   = ((uint32_t *)data)[1];

			lck_mtx_lock(&nspace_handler_lock);

			for(i=0; i < MAX_NSPACE_ITEMS; i++) {
				if (nspace_items[i].token == token) {
					break; /* exit for loop, not case statement */
				}
			}

			if (i >= MAX_NSPACE_ITEMS) {
				printf("nspace-handler-unblock: did not find token %u\n", token);
				error = ENOENT;
			} else {
				if (val == 0 && nspace_items[i].vp) {
					vnode_lock_spin(nspace_items[i].vp);
					nspace_items[i].vp->v_flag &= ~VNEEDSSNAPSHOT;
					vnode_unlock(nspace_items[i].vp);
				}

				nspace_items[i].vp = NULL;
				nspace_items[i].arg = NULL;
				nspace_items[i].op = 0;
				nspace_items[i].vid = 0;
				nspace_items[i].flags = NSPACE_ITEM_DONE;
				nspace_items[i].token = 0;

				wakeup((caddr_t)&(nspace_items[i].vp));
			}

			lck_mtx_unlock(&nspace_handler_lock);
		}
		break;

		case FSIOC_NAMESPACE_HANDLER_CANCEL: {
			uint32_t token, val;
			int i;

			if ((error = suser(kauth_cred_get(), &(p->p_acflag)))) {
				break;
			}

			if (!nspace_is_special_process(p)) {
				error = EINVAL;
				break;
			}

			token = ((uint32_t *)data)[0];
			val   = ((uint32_t *)data)[1];

			lck_mtx_lock(&nspace_handler_lock);

			for(i=0; i < MAX_NSPACE_ITEMS; i++) {
				if (nspace_items[i].token == token) {
					break;  /* exit for loop, not case stmt */
				}
			}

			if (i >= MAX_NSPACE_ITEMS) {
				printf("nspace-handler-cancel: did not find token %u\n", token);
				error = ENOENT;
			} else {
				if (nspace_items[i].vp) {
					vnode_lock_spin(nspace_items[i].vp);
					nspace_items[i].vp->v_flag &= ~VNEEDSSNAPSHOT;
					vnode_unlock(nspace_items[i].vp);
				}

				nspace_items[i].vp = NULL;
				nspace_items[i].arg = NULL;
				nspace_items[i].vid = 0;
				nspace_items[i].token = val;
				nspace_items[i].flags &= ~NSPACE_ITEM_PROCESSING;
				nspace_items[i].flags |= NSPACE_ITEM_CANCELLED;

				wakeup((caddr_t)&(nspace_items[i].vp));
			}

			lck_mtx_unlock(&nspace_handler_lock);
		}
		break;

		case FSIOC_NAMESPACE_HANDLER_SET_SNAPSHOT_TIME: {
			if ((error = suser(kauth_cred_get(), &(current_proc()->p_acflag)))) {
				break;
			}

			// we explicitly do not do the namespace_handler_proc check here

			lck_mtx_lock(&nspace_handler_lock);
			snapshot_timestamp = ((uint32_t *)data)[0];
			wakeup(&nspace_item_idx);
			lck_mtx_unlock(&nspace_handler_lock);
			printf("nspace-handler-set-snapshot-time: %d\n", (int)snapshot_timestamp);

		}
		break;

		case FSIOC_NAMESPACE_ALLOW_DMG_SNAPSHOT_EVENTS:
		{
			if ((error = suser(kauth_cred_get(), &(current_proc()->p_acflag)))) {
				break;
			}

			lck_mtx_lock(&nspace_handler_lock);
			nspace_allow_virtual_devs = ((uint32_t *)data)[0];
			lck_mtx_unlock(&nspace_handler_lock);
			printf("nspace-snapshot-handler will%s allow events on disk-images\n",
					nspace_allow_virtual_devs ? "" : " NOT");
			error = 0;

		}
		break;

		case FSIOC_SET_FSTYPENAME_OVERRIDE:
		{
			if ((error = suser(kauth_cred_get(), &(current_proc()->p_acflag)))) {
				break;
			}
			if (vp->v_mount) {
				mount_lock(vp->v_mount);
				if (data[0] != 0) {
					strlcpy(&vp->v_mount->fstypename_override[0], data, MFSTYPENAMELEN);
					vp->v_mount->mnt_kern_flag |= MNTK_TYPENAME_OVERRIDE;
					if (vfs_isrdonly(vp->v_mount) && strcmp(vp->v_mount->fstypename_override, "mtmfs") == 0) {
						vp->v_mount->mnt_kern_flag |= MNTK_EXTENDED_SECURITY;
						vp->v_mount->mnt_kern_flag &= ~MNTK_AUTH_OPAQUE;
					}
				} else {
					if (strcmp(vp->v_mount->fstypename_override, "mtmfs") == 0) {
						vp->v_mount->mnt_kern_flag &= ~MNTK_EXTENDED_SECURITY;
					}
					vp->v_mount->mnt_kern_flag &= ~MNTK_TYPENAME_OVERRIDE;
					vp->v_mount->fstypename_override[0] = '\0';
				}
				mount_unlock(vp->v_mount);
			}
		}
		break;

		case DISK_CONDITIONER_IOC_GET: {
		  error = disk_conditioner_get_info(vp->v_mount, (disk_conditioner_info *)data);
		}
		break;

		case DISK_CONDITIONER_IOC_SET: {
		  error = disk_conditioner_set_info(vp->v_mount, (disk_conditioner_info *)data);
		}
		break;

		default: {
			/* other, known commands shouldn't be passed down here */
			switch (cmd) {
				case F_PUNCHHOLE:
				case F_TRIM_ACTIVE_FILE:
				case F_RDADVISE:
				case F_TRANSCODEKEY:
				case F_GETPROTECTIONLEVEL:
				case F_GETDEFAULTPROTLEVEL:
				case F_MAKECOMPRESSED:
				case F_SET_GREEDY_MODE:
				case F_SETSTATICCONTENT:
				case F_SETIOTYPE:
				case F_SETBACKINGSTORE:
				case F_GETPATH_MTMINFO:
				case APFSIOC_REVERT_TO_SNAPSHOT:
				case FSIOC_FIOSEEKHOLE:
				case FSIOC_FIOSEEKDATA:
				case HFS_GET_BOOT_INFO:
				case HFS_SET_BOOT_INFO:
				case FIOPINSWAP:
				case F_CHKCLEAN:
				case F_FULLFSYNC:
				case F_BARRIERFSYNC:
				case F_FREEZE_FS:
				case F_THAW_FS:
					error = EINVAL;
					goto outdrop;
			}
			/* Invoke the filesystem-specific code */
			error = VNOP_IOCTL(vp, cmd, data, options, ctx);
		}

	} /* end switch stmt */

	/*
	 * if no errors, copy any data to user. Size was
	 * already set and checked above.
	 */
	if (error == 0 && (cmd & IOC_OUT) && size)
		error = copyout(data, udata, size);

outdrop:
	if (memp) {
		kfree(memp, size);
	}

	return error;
}