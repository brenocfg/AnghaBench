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
struct smb_vol {scalar_t__ dynperm; scalar_t__ cifs_acl; scalar_t__ sfu_emul; scalar_t__ mfsymlinks; scalar_t__ direct_io; scalar_t__ strict_io; scalar_t__ multiuser; scalar_t__ fsc; scalar_t__ override_gid; scalar_t__ override_uid; int /*<<< orphan*/  backupgid; scalar_t__ backupgid_specified; int /*<<< orphan*/  backupuid; scalar_t__ backupuid_specified; scalar_t__ rwpidforward; scalar_t__ mand_lock; scalar_t__ nostrictsync; scalar_t__ nobrl; scalar_t__ no_xattr; scalar_t__ remap; scalar_t__ server_ino; scalar_t__ setuids; scalar_t__ noperm; int /*<<< orphan*/  local_nls; int /*<<< orphan*/  actimeo; int /*<<< orphan*/  dir_mode; int /*<<< orphan*/  file_mode; int /*<<< orphan*/  linux_gid; int /*<<< orphan*/  linux_uid; int /*<<< orphan*/ * prepath; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  mnt_backupgid; int /*<<< orphan*/  mnt_backupuid; int /*<<< orphan*/  local_nls; int /*<<< orphan*/  actimeo; int /*<<< orphan*/  mnt_dir_mode; int /*<<< orphan*/  mnt_file_mode; int /*<<< orphan*/  mnt_gid; int /*<<< orphan*/  mnt_uid; scalar_t__ prepathlen; int /*<<< orphan*/ * prepath; int /*<<< orphan*/  tlink_tree; int /*<<< orphan*/  tlink_tree_lock; int /*<<< orphan*/  prune_tlinks; } ;

/* Variables and functions */
 int CIFS_MOUNT_CIFS_ACL ; 
 int CIFS_MOUNT_CIFS_BACKUPGID ; 
 int CIFS_MOUNT_CIFS_BACKUPUID ; 
 int CIFS_MOUNT_DIRECT_IO ; 
 int CIFS_MOUNT_DYNPERM ; 
 int CIFS_MOUNT_FSCACHE ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int CIFS_MOUNT_MF_SYMLINKS ; 
 int CIFS_MOUNT_MULTIUSER ; 
 int CIFS_MOUNT_NOPOSIXBRL ; 
 int CIFS_MOUNT_NOSSYNC ; 
 int CIFS_MOUNT_NO_BRL ; 
 int CIFS_MOUNT_NO_PERM ; 
 int CIFS_MOUNT_NO_XATTR ; 
 int CIFS_MOUNT_OVERR_GID ; 
 int CIFS_MOUNT_OVERR_UID ; 
 int CIFS_MOUNT_RWPIDFORWARD ; 
 int CIFS_MOUNT_SERVER_INUM ; 
 int CIFS_MOUNT_SET_UID ; 
 int CIFS_MOUNT_STRICT_IO ; 
 int CIFS_MOUNT_UNX_EMUL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  cERROR (int,char*) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int /*<<< orphan*/  cifs_prune_tlinks ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

void cifs_setup_cifs_sb(struct smb_vol *pvolume_info,
			struct cifs_sb_info *cifs_sb)
{
	INIT_DELAYED_WORK(&cifs_sb->prune_tlinks, cifs_prune_tlinks);

	spin_lock_init(&cifs_sb->tlink_tree_lock);
	cifs_sb->tlink_tree = RB_ROOT;

	/* calculate prepath */
	cifs_sb->prepath = pvolume_info->prepath;
	if (cifs_sb->prepath) {
		cifs_sb->prepathlen = strlen(cifs_sb->prepath);
		/* we can not convert the / to \ in the path
		separators in the prefixpath yet because we do not
		know (until reset_cifs_unix_caps is called later)
		whether POSIX PATH CAP is available. We normalize
		the / to \ after reset_cifs_unix_caps is called */
		pvolume_info->prepath = NULL;
	} else
		cifs_sb->prepathlen = 0;
	cifs_sb->mnt_uid = pvolume_info->linux_uid;
	cifs_sb->mnt_gid = pvolume_info->linux_gid;
	cifs_sb->mnt_file_mode = pvolume_info->file_mode;
	cifs_sb->mnt_dir_mode = pvolume_info->dir_mode;
	cFYI(1, "file mode: 0x%x  dir mode: 0x%x",
		cifs_sb->mnt_file_mode, cifs_sb->mnt_dir_mode);

	cifs_sb->actimeo = pvolume_info->actimeo;
	cifs_sb->local_nls = pvolume_info->local_nls;

	if (pvolume_info->noperm)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_NO_PERM;
	if (pvolume_info->setuids)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_SET_UID;
	if (pvolume_info->server_ino)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_SERVER_INUM;
	if (pvolume_info->remap)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_MAP_SPECIAL_CHR;
	if (pvolume_info->no_xattr)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_NO_XATTR;
	if (pvolume_info->sfu_emul)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_UNX_EMUL;
	if (pvolume_info->nobrl)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_NO_BRL;
	if (pvolume_info->nostrictsync)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_NOSSYNC;
	if (pvolume_info->mand_lock)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_NOPOSIXBRL;
	if (pvolume_info->rwpidforward)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_RWPIDFORWARD;
	if (pvolume_info->cifs_acl)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_CIFS_ACL;
	if (pvolume_info->backupuid_specified) {
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_CIFS_BACKUPUID;
		cifs_sb->mnt_backupuid = pvolume_info->backupuid;
	}
	if (pvolume_info->backupgid_specified) {
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_CIFS_BACKUPGID;
		cifs_sb->mnt_backupgid = pvolume_info->backupgid;
	}
	if (pvolume_info->override_uid)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_OVERR_UID;
	if (pvolume_info->override_gid)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_OVERR_GID;
	if (pvolume_info->dynperm)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_DYNPERM;
	if (pvolume_info->fsc)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_FSCACHE;
	if (pvolume_info->multiuser)
		cifs_sb->mnt_cifs_flags |= (CIFS_MOUNT_MULTIUSER |
					    CIFS_MOUNT_NO_PERM);
	if (pvolume_info->strict_io)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_STRICT_IO;
	if (pvolume_info->direct_io) {
		cFYI(1, "mounting share using direct i/o");
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_DIRECT_IO;
	}
	if (pvolume_info->mfsymlinks) {
		if (pvolume_info->sfu_emul) {
			cERROR(1,  "mount option mfsymlinks ignored if sfu "
				   "mount option is used");
		} else {
			cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_MF_SYMLINKS;
		}
	}

	if ((pvolume_info->cifs_acl) && (pvolume_info->dynperm))
		cERROR(1, "mount option dynperm ignored if cifsacl "
			   "mount option supported");
}