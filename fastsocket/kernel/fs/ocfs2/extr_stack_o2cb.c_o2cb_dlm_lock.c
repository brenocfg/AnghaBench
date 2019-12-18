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
union ocfs2_dlm_lksb {int /*<<< orphan*/  lksb_o2dlm; } ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_cluster_connection {int /*<<< orphan*/  cc_lockspace; } ;
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;

/* Variables and functions */
 int dlm_status_to_errno (int) ; 
 int dlmlock (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,void*,unsigned int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int flags_to_o2dlm (int /*<<< orphan*/ ) ; 
 int mode_to_o2dlm (int) ; 
 int /*<<< orphan*/  o2dlm_blocking_ast_wrapper ; 
 int /*<<< orphan*/  o2dlm_lock_ast_wrapper ; 

__attribute__((used)) static int o2cb_dlm_lock(struct ocfs2_cluster_connection *conn,
			 int mode,
			 union ocfs2_dlm_lksb *lksb,
			 u32 flags,
			 void *name,
			 unsigned int namelen,
			 void *astarg)
{
	enum dlm_status status;
	int o2dlm_mode = mode_to_o2dlm(mode);
	int o2dlm_flags = flags_to_o2dlm(flags);
	int ret;

	status = dlmlock(conn->cc_lockspace, o2dlm_mode, &lksb->lksb_o2dlm,
			 o2dlm_flags, name, namelen,
			 o2dlm_lock_ast_wrapper, astarg,
			 o2dlm_blocking_ast_wrapper);
	ret = dlm_status_to_errno(status);
	return ret;
}