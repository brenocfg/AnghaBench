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
typedef  int /*<<< orphan*/  uid_t ;
struct super_block {int s_flags; int s_dirt; } ;
struct affs_sb_info {unsigned long s_flags; int s_mode; int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; int /*<<< orphan*/  s_volume; int /*<<< orphan*/  s_prefix; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 struct affs_sb_info* AFFS_SB (struct super_block*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MS_NODIRATIME ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  affs_free_bitmap (struct super_block*) ; 
 int affs_init_bitmap (struct super_block*,int*) ; 
 int /*<<< orphan*/  affs_write_super (struct super_block*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  parse_options (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,char*) ; 
 int /*<<< orphan*/  replace_mount_options (struct super_block*,char*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
affs_remount(struct super_block *sb, int *flags, char *data)
{
	struct affs_sb_info	*sbi = AFFS_SB(sb);
	int			 blocksize;
	uid_t			 uid;
	gid_t			 gid;
	int			 mode;
	int			 reserved;
	int			 root_block;
	unsigned long		 mount_flags;
	int			 res = 0;
	char			*new_opts = kstrdup(data, GFP_KERNEL);

	pr_debug("AFFS: remount(flags=0x%x,opts=\"%s\")\n",*flags,data);

	*flags |= MS_NODIRATIME;

	if (!parse_options(data, &uid, &gid, &mode, &reserved, &root_block,
			   &blocksize, &sbi->s_prefix, sbi->s_volume,
			   &mount_flags)) {
		kfree(new_opts);
		return -EINVAL;
	}
	lock_kernel();
	replace_mount_options(sb, new_opts);

	sbi->s_flags = mount_flags;
	sbi->s_mode  = mode;
	sbi->s_uid   = uid;
	sbi->s_gid   = gid;

	if ((*flags & MS_RDONLY) == (sb->s_flags & MS_RDONLY)) {
		unlock_kernel();
		return 0;
	}
	if (*flags & MS_RDONLY) {
		sb->s_dirt = 1;
		while (sb->s_dirt)
			affs_write_super(sb);
		affs_free_bitmap(sb);
	} else
		res = affs_init_bitmap(sb, flags);

	unlock_kernel();
	return res;
}