#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {int f_pos; TYPE_2__ f_path; } ;
struct autofs_dirhash {int dummy; } ;
struct autofs_sb_info {struct autofs_dirhash dirhash; } ;
struct autofs_dir_ent {char* name; int len; int /*<<< orphan*/  ino; int /*<<< orphan*/  dentry; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  (* filldir_t ) (void*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_UNKNOWN ; 
 struct autofs_dir_ent* autofs_hash_enum (struct autofs_dirhash*,int*,struct autofs_dir_ent*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_mountpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int autofs_root_readdir(struct file *filp, void *dirent, filldir_t filldir)
{
	struct autofs_dir_ent *ent = NULL;
	struct autofs_dirhash *dirhash;
	struct autofs_sb_info *sbi;
	struct inode * inode = filp->f_path.dentry->d_inode;
	off_t onr, nr;

	lock_kernel();

	sbi = autofs_sbi(inode->i_sb);
	dirhash = &sbi->dirhash;
	nr = filp->f_pos;

	switch(nr)
	{
	case 0:
		if (filldir(dirent, ".", 1, nr, inode->i_ino, DT_DIR) < 0)
			goto out;
		filp->f_pos = ++nr;
		/* fall through */
	case 1:
		if (filldir(dirent, "..", 2, nr, inode->i_ino, DT_DIR) < 0)
			goto out;
		filp->f_pos = ++nr;
		/* fall through */
	default:
		while (onr = nr, ent = autofs_hash_enum(dirhash,&nr,ent)) {
			if (!ent->dentry || d_mountpoint(ent->dentry)) {
				if (filldir(dirent,ent->name,ent->len,onr,ent->ino,DT_UNKNOWN) < 0)
					goto out;
				filp->f_pos = nr;
			}
		}
		break;
	}

out:
	unlock_kernel();
	return 0;
}