#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smb_sb_info {TYPE_1__* mnt; } ;
struct smb_fattr {int f_nlink; scalar_t__ f_unix; int /*<<< orphan*/  f_gid; int /*<<< orphan*/  f_uid; } ;
struct TYPE_2__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct smb_fattr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
smb_init_dirent(struct smb_sb_info *server, struct smb_fattr *fattr)
{
	memset(fattr, 0, sizeof(*fattr));

	fattr->f_nlink = 1;
	fattr->f_uid = server->mnt->uid;
	fattr->f_gid = server->mnt->gid;
	fattr->f_unix = 0;
}