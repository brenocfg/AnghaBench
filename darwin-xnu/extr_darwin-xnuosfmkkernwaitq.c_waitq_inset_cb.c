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
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ left_setid; scalar_t__ right_setid; } ;
struct TYPE_3__ {scalar_t__ id; } ;
struct waitq_link {TYPE_2__ wql_link; TYPE_1__ wql_setid; } ;
struct waitq {int dummy; } ;

/* Variables and functions */
 int WQL_LINK ; 
 int WQL_WQS ; 
 int WQ_ITERATE_CONTINUE ; 
 int WQ_ITERATE_FOUND ; 
 int /*<<< orphan*/  wqdbg_v (char*,scalar_t__) ; 
 int wql_type (struct waitq_link*) ; 

__attribute__((used)) static int waitq_inset_cb(struct waitq *waitq, void *ctx, struct waitq_link *link)
{
	uint64_t setid = *(uint64_t *)ctx;
	int wqltype = wql_type(link);
	(void)waitq;
	if (wqltype == WQL_WQS && link->wql_setid.id == setid) {
		wqdbg_v("  waitq already in set 0x%llx", setid);
		return WQ_ITERATE_FOUND;
	} else if (wqltype == WQL_LINK) {
		/*
		 * break out early if we see a link that points to the setid
		 * in question. This saves us a step in the
		 * iteration/recursion
		 */
		wqdbg_v("  waitq already in set 0x%llx (WQL_LINK)", setid);
		if (link->wql_link.left_setid == setid ||
		    link->wql_link.right_setid == setid)
			return WQ_ITERATE_FOUND;
	}

	return WQ_ITERATE_CONTINUE;
}