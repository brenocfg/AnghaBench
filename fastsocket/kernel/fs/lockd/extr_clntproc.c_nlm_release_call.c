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
struct nlm_rqst {int /*<<< orphan*/  a_host; int /*<<< orphan*/  a_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nlm_rqst*) ; 
 int /*<<< orphan*/  nlm_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmclnt_release_lockargs (struct nlm_rqst*) ; 

void nlm_release_call(struct nlm_rqst *call)
{
	if (!atomic_dec_and_test(&call->a_count))
		return;
	nlm_release_host(call->a_host);
	nlmclnt_release_lockargs(call);
	kfree(call);
}