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
struct vnode_trace_paths_context {int count; scalar_t__ path; } ;
struct vnode {int dummy; } ;

/* Variables and functions */
 int KDBG_VFS_LOOKUP_FLAG_LOOKUP ; 
 int KDBG_VFS_LOOKUP_FLAG_NOPROCFILT ; 
 int VNODE_RETURNED ; 
 int /*<<< orphan*/  kdebug_vfs_lookup (scalar_t__,int,struct vnode*,int) ; 
 int /*<<< orphan*/  thread_yield_to_preemption () ; 
 int vn_getpath (struct vnode*,char*,int*) ; 

__attribute__((used)) static int vnode_trace_path_callback(struct vnode *vp, void *arg) {
	int len, rv;
	struct vnode_trace_paths_context *ctx;

	ctx = arg;

	len = sizeof (ctx->path);
	rv = vn_getpath(vp, (char *)ctx->path, &len);
	/* vn_getpath() NUL-terminates, and len includes the NUL */

	if (!rv) {
		kdebug_vfs_lookup(ctx->path, len, vp,
				KDBG_VFS_LOOKUP_FLAG_LOOKUP | KDBG_VFS_LOOKUP_FLAG_NOPROCFILT);

		if (++(ctx->count) == 1000) {
			thread_yield_to_preemption();
			ctx->count = 0;
		}
	}

	return VNODE_RETURNED;
}