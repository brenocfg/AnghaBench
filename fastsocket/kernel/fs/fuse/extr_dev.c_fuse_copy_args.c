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
struct fuse_copy_state {int dummy; } ;
struct fuse_arg {int /*<<< orphan*/  size; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int fuse_copy_one (struct fuse_copy_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fuse_copy_pages (struct fuse_copy_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fuse_copy_args(struct fuse_copy_state *cs, unsigned numargs,
			  unsigned argpages, struct fuse_arg *args,
			  int zeroing)
{
	int err = 0;
	unsigned i;

	for (i = 0; !err && i < numargs; i++)  {
		struct fuse_arg *arg = &args[i];
		if (i == numargs - 1 && argpages)
			err = fuse_copy_pages(cs, arg->size, zeroing);
		else
			err = fuse_copy_one(cs, arg->value, arg->size);
	}
	return err;
}