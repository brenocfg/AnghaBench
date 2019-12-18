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
struct request_sock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dreq_featneg; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pktopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_feat_list_purge (int /*<<< orphan*/ *) ; 
 TYPE_2__* dccp_rsk (struct request_sock*) ; 
 TYPE_1__* inet6_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dccp_v6_reqsk_destructor(struct request_sock *req)
{
	dccp_feat_list_purge(&dccp_rsk(req)->dreq_featneg);
	if (inet6_rsk(req)->pktopts != NULL)
		kfree_skb(inet6_rsk(req)->pktopts);
}