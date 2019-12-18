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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_sec_ctx {int /*<<< orphan*/  ctx_sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOCIATION__POLMATCH ; 
 int EACCES ; 
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  SECCLASS_ASSOCIATION ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_authorizable_ctx (struct xfrm_sec_ctx*) ; 

int selinux_xfrm_policy_lookup(struct xfrm_sec_ctx *ctx, u32 fl_secid, u8 dir)
{
	int rc;
	u32 sel_sid;

	/* Context sid is either set to label or ANY_ASSOC */
	if (ctx) {
		if (!selinux_authorizable_ctx(ctx))
			return -EINVAL;

		sel_sid = ctx->ctx_sid;
	} else
		/*
		 * All flows should be treated as polmatch'ing an
		 * otherwise applicable "non-labeled" policy. This
		 * would prevent inadvertent "leaks".
		 */
		return 0;

	rc = avc_has_perm(fl_secid, sel_sid, SECCLASS_ASSOCIATION,
			  ASSOCIATION__POLMATCH,
			  NULL);

	if (rc == -EACCES)
		return -ESRCH;

	return rc;
}