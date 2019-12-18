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
struct path {TYPE_1__* mnt; } ;
struct file {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  mnt_sb; } ;

/* Variables and functions */
 int EINVAL ; 
 int kern_path (char*,int /*<<< orphan*/ ,struct path*) ; 
 int nlmsvc_unlock_all_by_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 scalar_t__ qword_get (char**,char*,size_t) ; 

__attribute__((used)) static ssize_t write_unlock_fs(struct file *file, char *buf, size_t size)
{
	struct path path;
	char *fo_path;
	int error;

	/* sanity check */
	if (size == 0)
		return -EINVAL;

	if (buf[size-1] != '\n')
		return -EINVAL;

	fo_path = buf;
	if (qword_get(&buf, fo_path, size) < 0)
		return -EINVAL;

	error = kern_path(fo_path, 0, &path);
	if (error)
		return error;

	/*
	 * XXX: Needs better sanity checking.  Otherwise we could end up
	 * releasing locks on the wrong file system.
	 *
	 * For example:
	 * 1.  Does the path refer to a directory?
	 * 2.  Is that directory a mount point, or
	 * 3.  Is that directory the root of an exported file system?
	 */
	error = nlmsvc_unlock_all_by_sb(path.mnt->mnt_sb);

	path_put(&path);
	return error;
}