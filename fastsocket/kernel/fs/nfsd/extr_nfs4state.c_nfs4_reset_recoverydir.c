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
struct path {TYPE_2__* dentry; } ;
struct TYPE_4__ {TYPE_1__* d_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int ENOTDIR ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int kern_path (char*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  nfs4_set_recdir (char*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 

int
nfs4_reset_recoverydir(char *recdir)
{
	int status;
	struct path path;

	status = kern_path(recdir, LOOKUP_FOLLOW, &path);
	if (status)
		return status;
	status = -ENOTDIR;
	if (S_ISDIR(path.dentry->d_inode->i_mode)) {
		nfs4_set_recdir(recdir);
		status = 0;
	}
	path_put(&path);
	return status;
}