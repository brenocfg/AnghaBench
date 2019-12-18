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
struct dentry {int /*<<< orphan*/  d_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_UNHASHED ; 

__attribute__((used)) static int anon_inodefs_delete_dentry(struct dentry *dentry)
{
	/*
	 * We faked vfs to believe the dentry was hashed when we created it.
	 * Now we restore the flag so that dput() will work correctly.
	 */
	dentry->d_flags |= DCACHE_UNHASHED;
	return 1;
}