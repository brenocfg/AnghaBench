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
struct kdp_callout {struct kdp_callout* callout_next; int /*<<< orphan*/  callout_in_progress; void* callout_arg; int /*<<< orphan*/  callout_fn; } ;
typedef  int /*<<< orphan*/  kdp_callout_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OSCompareAndSwapPtr (struct kdp_callout*,struct kdp_callout*,struct kdp_callout**) ; 
 struct kdp_callout* kalloc (int) ; 
 struct kdp_callout* kdp_callout_list ; 
 int /*<<< orphan*/  panic (char*) ; 

void
kdp_register_callout(kdp_callout_fn_t fn, void * arg)
{
	struct kdp_callout * kcp;
	struct kdp_callout * list_head;

	kcp = kalloc(sizeof(*kcp));
	if (kcp == NULL)
		panic("kdp_register_callout() kalloc failed");

	kcp->callout_fn = fn;
	kcp->callout_arg = arg;
	kcp->callout_in_progress = FALSE;

	/* Lock-less list insertion using compare and exchange. */
	do {
		list_head = kdp_callout_list;
		kcp->callout_next = list_head;
	} while (!OSCompareAndSwapPtr(list_head, kcp, &kdp_callout_list));
}