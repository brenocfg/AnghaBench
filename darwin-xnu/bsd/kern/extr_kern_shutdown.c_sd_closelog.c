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
typedef  int /*<<< orphan*/  vfs_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  FWRITE ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 scalar_t__ NULLVP ; 
 int /*<<< orphan*/  VNOP_FSYNC (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_logvp ; 
 int vnode_close (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sd_closelog(vfs_context_t ctx)
{
	int error = 0;
	if (sd_logvp != NULLVP) {
		VNOP_FSYNC(sd_logvp, MNT_WAIT, ctx);
		error = vnode_close(sd_logvp, FWRITE, ctx);
	}

	return error;
}