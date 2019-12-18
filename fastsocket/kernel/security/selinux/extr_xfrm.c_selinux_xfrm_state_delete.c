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
struct xfrm_state {struct xfrm_sec_ctx* security; } ;
struct xfrm_sec_ctx {int /*<<< orphan*/  ctx_sid; } ;
struct task_security_struct {int /*<<< orphan*/  sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOCIATION__SETCONTEXT ; 
 int /*<<< orphan*/  SECCLASS_ASSOCIATION ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct task_security_struct* current_security () ; 
 int /*<<< orphan*/  selinux_xfrm_refcount ; 

int selinux_xfrm_state_delete(struct xfrm_state *x)
{
	const struct task_security_struct *tsec = current_security();
	struct xfrm_sec_ctx *ctx = x->security;
	int rc = 0;

	if (ctx) {
		rc = avc_has_perm(tsec->sid, ctx->ctx_sid,
				  SECCLASS_ASSOCIATION,
				  ASSOCIATION__SETCONTEXT, NULL);
		if (rc == 0)
			atomic_dec(&selinux_xfrm_refcount);
	}

	return rc;
}