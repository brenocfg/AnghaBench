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
struct sk_buff {int dummy; } ;
struct netlink_callback {int* args; } ;
struct TYPE_2__ {int nchunks; int size; scalar_t__ trace_addr; int /*<<< orphan*/  enabled; } ;
struct iwl_test {TYPE_1__ trace; } ;

/* Variables and functions */
 int DUMP_CHUNK_SIZE ; 
 int EFAULT ; 
 int ENOBUFS ; 
 int ENOENT ; 
 int /*<<< orphan*/  IWL_TM_ATTR_TRACE_DUMP ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int iwl_test_trace_dump(struct iwl_test *tst, struct sk_buff *skb,
			       struct netlink_callback *cb)
{
	int idx, length;

	if (!tst->trace.enabled || !tst->trace.trace_addr)
		return -EFAULT;

	idx = cb->args[4];
	if (idx >= tst->trace.nchunks)
		return -ENOENT;

	length = DUMP_CHUNK_SIZE;
	if (((idx + 1) == tst->trace.nchunks) &&
	    (tst->trace.size % DUMP_CHUNK_SIZE))
		length = tst->trace.size %
			DUMP_CHUNK_SIZE;

	if (nla_put(skb, IWL_TM_ATTR_TRACE_DUMP, length,
		    tst->trace.trace_addr + (DUMP_CHUNK_SIZE * idx)))
		goto nla_put_failure;

	cb->args[4] = ++idx;
	return 0;

 nla_put_failure:
	return -ENOBUFS;
}