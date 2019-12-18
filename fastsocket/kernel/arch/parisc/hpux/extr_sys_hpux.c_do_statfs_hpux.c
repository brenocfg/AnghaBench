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
struct path {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * val; } ;
struct kstatfs {TYPE_1__ f_fsid; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct hpux_statfs {int /*<<< orphan*/ * f_fsid; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct hpux_statfs*,int /*<<< orphan*/ ,int) ; 
 int vfs_statfs (struct path*,struct kstatfs*) ; 

__attribute__((used)) static int do_statfs_hpux(struct path *path, struct hpux_statfs *buf)
{
	struct kstatfs st;
	int retval;
	
	retval = vfs_statfs(path, &st);
	if (retval)
		return retval;

	memset(buf, 0, sizeof(*buf));
	buf->f_type = st.f_type;
	buf->f_bsize = st.f_bsize;
	buf->f_blocks = st.f_blocks;
	buf->f_bfree = st.f_bfree;
	buf->f_bavail = st.f_bavail;
	buf->f_files = st.f_files;
	buf->f_ffree = st.f_ffree;
	buf->f_fsid[0] = st.f_fsid.val[0];
	buf->f_fsid[1] = st.f_fsid.val[1];

	return 0;
}