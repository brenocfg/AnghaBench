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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  dirEntNum; int /*<<< orphan*/  volNumber; int /*<<< orphan*/  file_handle; int /*<<< orphan*/  opened; } ;

/* Variables and functions */
 TYPE_1__* NCP_FINFO (struct inode*) ; 
 int /*<<< orphan*/  NCP_SERVER (struct inode*) ; 
 int /*<<< orphan*/  PPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ncp_close_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ncp_make_closed(struct inode *inode)
{
	int err;

	err = 0;
	mutex_lock(&NCP_FINFO(inode)->open_mutex);
	if (atomic_read(&NCP_FINFO(inode)->opened) == 1) {
		atomic_set(&NCP_FINFO(inode)->opened, 0);
		err = ncp_close_file(NCP_SERVER(inode), NCP_FINFO(inode)->file_handle);

		if (!err)
			PPRINTK("ncp_make_closed: volnum=%d, dirent=%u, error=%d\n",
				NCP_FINFO(inode)->volNumber,
				NCP_FINFO(inode)->dirEntNum, err);
	}
	mutex_unlock(&NCP_FINFO(inode)->open_mutex);
	return err;
}