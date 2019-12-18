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
struct path {struct dentry* member_1; int /*<<< orphan*/  member_0; int /*<<< orphan*/  mnt; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
#define  S_IFBLK 131 
#define  S_IFCHR 130 
#define  S_IFIFO 129 
 int S_IFMT ; 
#define  S_IFSOCK 128 
 int TOMOYO_TYPE_CREATE_ACL ; 
 int TOMOYO_TYPE_MKBLOCK_ACL ; 
 int TOMOYO_TYPE_MKCHAR_ACL ; 
 int TOMOYO_TYPE_MKFIFO_ACL ; 
 int TOMOYO_TYPE_MKSOCK_ACL ; 
 int tomoyo_check_1path_perm (int /*<<< orphan*/ ,int,struct path*) ; 
 int /*<<< orphan*/  tomoyo_domain () ; 

__attribute__((used)) static int tomoyo_path_mknod(struct path *parent, struct dentry *dentry,
			     int mode, unsigned int dev)
{
	struct path path = { parent->mnt, dentry };
	int type = TOMOYO_TYPE_CREATE_ACL;

	switch (mode & S_IFMT) {
	case S_IFCHR:
		type = TOMOYO_TYPE_MKCHAR_ACL;
		break;
	case S_IFBLK:
		type = TOMOYO_TYPE_MKBLOCK_ACL;
		break;
	case S_IFIFO:
		type = TOMOYO_TYPE_MKFIFO_ACL;
		break;
	case S_IFSOCK:
		type = TOMOYO_TYPE_MKSOCK_ACL;
		break;
	}
	return tomoyo_check_1path_perm(tomoyo_domain(),
				       type, &path);
}