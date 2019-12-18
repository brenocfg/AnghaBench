#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fl; } ;
struct TYPE_8__ {TYPE_3__ lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  fl; } ;
struct TYPE_6__ {TYPE_1__ lock; } ;
struct nlm_rqst {struct nlm_host* a_host; TYPE_4__ a_res; TYPE_2__ a_args; int /*<<< orphan*/  a_count; } ;
struct nlm_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct nlm_rqst* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locks_init_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_release_host (struct nlm_host*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 scalar_t__ signalled () ; 

struct nlm_rqst *nlm_alloc_call(struct nlm_host *host)
{
	struct nlm_rqst	*call;

	for(;;) {
		call = kzalloc(sizeof(*call), GFP_KERNEL);
		if (call != NULL) {
			atomic_set(&call->a_count, 1);
			locks_init_lock(&call->a_args.lock.fl);
			locks_init_lock(&call->a_res.lock.fl);
			call->a_host = host;
			return call;
		}
		if (signalled())
			break;
		printk("nlm_alloc_call: failed, waiting for memory\n");
		schedule_timeout_interruptible(5*HZ);
	}
	nlm_release_host(host);
	return NULL;
}