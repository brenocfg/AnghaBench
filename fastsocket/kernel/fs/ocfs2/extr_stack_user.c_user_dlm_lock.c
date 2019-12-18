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
struct TYPE_2__ {char* sb_lvbptr; } ;
union ocfs2_dlm_lksb {TYPE_1__ lksb_fsdlm; } ;
typedef  int u32 ;
struct ocfs2_cluster_connection {int /*<<< orphan*/  cc_lockspace; } ;
struct dlm_lksb {int dummy; } ;

/* Variables and functions */
 int DLM_LKF_NODLCKWT ; 
 int dlm_lock (int /*<<< orphan*/ ,int,TYPE_1__*,int,void*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsdlm_blocking_ast_wrapper ; 
 int /*<<< orphan*/  fsdlm_lock_ast_wrapper ; 

__attribute__((used)) static int user_dlm_lock(struct ocfs2_cluster_connection *conn,
			 int mode,
			 union ocfs2_dlm_lksb *lksb,
			 u32 flags,
			 void *name,
			 unsigned int namelen,
			 void *astarg)
{
	int ret;

	if (!lksb->lksb_fsdlm.sb_lvbptr)
		lksb->lksb_fsdlm.sb_lvbptr = (char *)lksb +
					     sizeof(struct dlm_lksb);

	ret = dlm_lock(conn->cc_lockspace, mode, &lksb->lksb_fsdlm,
		       flags|DLM_LKF_NODLCKWT, name, namelen, 0,
		       fsdlm_lock_ast_wrapper, astarg,
		       fsdlm_blocking_ast_wrapper);
	return ret;
}