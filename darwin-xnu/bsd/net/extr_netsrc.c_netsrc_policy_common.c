#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
struct netsrc_req {TYPE_2__ nrq_dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  sa; } ;
struct netsrc_rep {int nrp_dstlabel; int nrp_label; int /*<<< orphan*/  nrp_precedence; TYPE_1__ nrp_src; int /*<<< orphan*/  nrp_dstprecedence; } ;
struct in6_addrpolicy {int label; int /*<<< orphan*/  preced; } ;

/* Variables and functions */
 struct in6_addrpolicy* lookup_policy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
netsrc_policy_common(struct netsrc_req *request, struct netsrc_rep *reply)
{
	// Destination policy
	struct in6_addrpolicy *policy = lookup_policy(&request->nrq_dst.sa);
	if (policy != NULL && policy->label != -1) {
		reply->nrp_dstlabel = policy->label;
		reply->nrp_dstprecedence = policy->preced;
	}

	// Source policy
	policy = lookup_policy(&reply->nrp_src.sa);
	if (policy != NULL && policy->label != -1) {
		reply->nrp_label = policy->label;
		reply->nrp_precedence = policy->preced;
	}
}