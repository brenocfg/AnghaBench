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
 int dlmunlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 
 int flags_to_o2dlm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2dlm_unlock_ast_wrapper ; 

__attribute__((used)) static int o2cb_dlm_unlock(struct ocfs2_cluster_connection *conn,
			   union ocfs2_dlm_lksb *lksb,
			   u32 flags,
			   void *astarg)
{
	enum dlm_status status;
	int o2dlm_flags = flags_to_o2dlm(flags);
	int ret;

	status = dlmunlock(conn->cc_lockspace, &lksb->lksb_o2dlm,
			   o2dlm_flags, o2dlm_unlock_ast_wrapper, astarg);
	ret = dlm_status_to_errno(status);
	return ret;
}