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
struct xfrm_user_sec_ctx {int dummy; } ;
struct xfrm_policy {int /*<<< orphan*/  security; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 size_t XFRMA_SEC_CTX ; 
 struct xfrm_user_sec_ctx* nla_data (struct nlattr*) ; 
 int security_xfrm_policy_alloc (int /*<<< orphan*/ *,struct xfrm_user_sec_ctx*) ; 

__attribute__((used)) static int copy_from_user_sec_ctx(struct xfrm_policy *pol, struct nlattr **attrs)
{
	struct nlattr *rt = attrs[XFRMA_SEC_CTX];
	struct xfrm_user_sec_ctx *uctx;

	if (!rt)
		return 0;

	uctx = nla_data(rt);
	return security_xfrm_policy_alloc(&pol->security, uctx);
}