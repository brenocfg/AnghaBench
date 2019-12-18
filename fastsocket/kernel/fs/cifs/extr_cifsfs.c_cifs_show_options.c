#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {TYPE_5__* mnt_sb; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct seq_file {int dummy; } ;
struct cifs_tcon {int treeName; scalar_t__ unix_ext; scalar_t__ retry; scalar_t__ nocase; scalar_t__ seal; TYPE_2__* ses; } ;
struct cifs_sb_info {int mnt_cifs_flags; int mnt_uid; int mnt_gid; int prepath; int mnt_backupuid; int mnt_backupgid; int rsize; int wsize; int actimeo; int /*<<< orphan*/  mnt_dir_mode; int /*<<< orphan*/  mnt_file_mode; } ;
struct TYPE_9__ {int s_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  srcaddr; } ;
struct TYPE_7__ {int user_name; int domainName; TYPE_3__* server; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int CIFS_MOUNT_CIFS_ACL ; 
 int CIFS_MOUNT_CIFS_BACKUPGID ; 
 int CIFS_MOUNT_CIFS_BACKUPUID ; 
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
 int CIFS_MOUNT_POSIX_PATHS ; 
 int CIFS_MOUNT_RWPIDFORWARD ; 
 int CIFS_MOUNT_SERVER_INUM ; 
 int CIFS_MOUNT_SET_UID ; 
 int CIFS_MOUNT_UNX_EMUL ; 
 struct cifs_sb_info* CIFS_SB (TYPE_5__*) ; 
 int HZ ; 
 int MS_POSIXACL ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_show_address (struct seq_file*,TYPE_3__*) ; 
 int /*<<< orphan*/  cifs_show_cache_flavor (struct seq_file*,struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_show_security (struct seq_file*,TYPE_3__*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int
cifs_show_options(struct seq_file *s, struct vfsmount *m)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(m->mnt_sb);
	struct cifs_tcon *tcon = cifs_sb_master_tcon(cifs_sb);
	struct sockaddr *srcaddr;
	srcaddr = (struct sockaddr *)&tcon->ses->server->srcaddr;

	cifs_show_security(s, tcon->ses->server);
	cifs_show_cache_flavor(s, cifs_sb);

	seq_printf(s, ",unc=%s", tcon->treeName);

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MULTIUSER)
		seq_printf(s, ",multiuser");
	else if (tcon->ses->user_name)
		seq_printf(s, ",username=%s", tcon->ses->user_name);

	if (tcon->ses->domainName)
		seq_printf(s, ",domain=%s", tcon->ses->domainName);

	if (srcaddr->sa_family != AF_UNSPEC) {
		struct sockaddr_in *saddr4;
		struct sockaddr_in6 *saddr6;
		saddr4 = (struct sockaddr_in *)srcaddr;
		saddr6 = (struct sockaddr_in6 *)srcaddr;
		if (srcaddr->sa_family == AF_INET6)
			seq_printf(s, ",srcaddr=%pI6c",
				   &saddr6->sin6_addr);
		else if (srcaddr->sa_family == AF_INET)
			seq_printf(s, ",srcaddr=%pI4",
				   &saddr4->sin_addr.s_addr);
		else
			seq_printf(s, ",srcaddr=BAD-AF:%i",
				   (int)(srcaddr->sa_family));
	}

	seq_printf(s, ",uid=%u", cifs_sb->mnt_uid);
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_OVERR_UID)
		seq_printf(s, ",forceuid");
	else
		seq_printf(s, ",noforceuid");

	seq_printf(s, ",gid=%u", cifs_sb->mnt_gid);
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_OVERR_GID)
		seq_printf(s, ",forcegid");
	else
		seq_printf(s, ",noforcegid");

	cifs_show_address(s, tcon->ses->server);

	if (!tcon->unix_ext)
		seq_printf(s, ",file_mode=0%o,dir_mode=0%o",
					   cifs_sb->mnt_file_mode,
					   cifs_sb->mnt_dir_mode);
	if (tcon->seal)
		seq_printf(s, ",seal");
	if (tcon->nocase)
		seq_printf(s, ",nocase");
	if (tcon->retry)
		seq_printf(s, ",hard");
	if (tcon->unix_ext)
		seq_printf(s, ",unix");
	else
		seq_printf(s, ",nounix");
	if (cifs_sb->prepath)
		seq_printf(s, ",prepath=%s", cifs_sb->prepath);
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_POSIX_PATHS)
		seq_printf(s, ",posixpaths");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SET_UID)
		seq_printf(s, ",setuids");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM)
		seq_printf(s, ",serverino");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_RWPIDFORWARD)
		seq_printf(s, ",rwpidforward");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NOPOSIXBRL)
		seq_printf(s, ",forcemand");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_XATTR)
		seq_printf(s, ",nouser_xattr");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MAP_SPECIAL_CHR)
		seq_printf(s, ",mapchars");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_UNX_EMUL)
		seq_printf(s, ",sfu");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_BRL)
		seq_printf(s, ",nobrl");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_ACL)
		seq_printf(s, ",cifsacl");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_DYNPERM)
		seq_printf(s, ",dynperm");
	if (m->mnt_sb->s_flags & MS_POSIXACL)
		seq_printf(s, ",acl");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MF_SYMLINKS)
		seq_printf(s, ",mfsymlinks");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_FSCACHE)
		seq_printf(s, ",fsc");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NOSSYNC)
		seq_printf(s, ",nostrictsync");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_PERM)
		seq_printf(s, ",noperm");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_BACKUPUID)
		seq_printf(s, ",backupuid=%u", cifs_sb->mnt_backupuid);
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_BACKUPGID)
		seq_printf(s, ",backupgid=%u", cifs_sb->mnt_backupgid);

	seq_printf(s, ",rsize=%u", cifs_sb->rsize);
	seq_printf(s, ",wsize=%u", cifs_sb->wsize);
	/* convert actimeo and display it in seconds */
	seq_printf(s, ",actimeo=%lu", cifs_sb->actimeo / HZ);

	return 0;
}