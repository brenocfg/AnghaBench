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
typedef  int /*<<< orphan*/  devnode_t ;
typedef  int /*<<< orphan*/  devdirent_t ;
struct TYPE_2__ {int /*<<< orphan*/ * de_dnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_free_name (int /*<<< orphan*/ *) ; 
 TYPE_1__* dev_root ; 
 int devfs_make_symlink (int /*<<< orphan*/ *,char*,int,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
devfs_fdesc_makelinks()
{
	int error = 0;
	devdirent_t *stdin_ent = NULL, *stdout_ent = NULL, *stderr_ent = NULL;
	devnode_t *root_devnode = dev_root->de_dnp;

	/* We do this ugliness to get around some "const" warnings */
	char in[] = "stdin";
	char out[] = "stdout";
	char err[] = "stderr";
	char zero[] = "fd/0";
	char one[] = "fd/1";
	char two[] = "fd/2";

	if ((error = devfs_make_symlink(root_devnode, in, 0555, zero, &stdin_ent))) {
		printf("Couldn't make stdin, err %d.\n", error);
		goto bad;
	}

	if ((error = devfs_make_symlink(root_devnode, out, 0555, one, &stdout_ent))) {
		printf("Couldn't make stdout, err %d.\n", error);
		goto bad;
	}

	if ((error = devfs_make_symlink(root_devnode, err, 0555, two, &stderr_ent))) {
		printf("Couldn't make stderr, err %d.\n", error);
		goto bad;
	}
	
	return 0;

bad:
	if (stdin_ent) {
		dev_free_name(stdin_ent);
	}
	if (stdout_ent) {
		dev_free_name(stdout_ent);
	}
	if (stderr_ent) {
		dev_free_name(stderr_ent);
	}

	return error;
}