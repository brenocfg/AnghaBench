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
struct TYPE_3__ {void* right_setid; void* left_setid; } ;
struct TYPE_4__ {int /*<<< orphan*/  wql_set; } ;
struct waitq_link {int /*<<< orphan*/  sl_free_ts; int /*<<< orphan*/  sl_alloc_th; scalar_t__ sl_mkvalid_ts; int /*<<< orphan*/  sl_mkvalid_bt; scalar_t__ sl_alloc_ts; int /*<<< orphan*/  sl_alloc_bt; TYPE_1__ wql_link; TYPE_2__ wql_wqs; } ;
struct lt_elem {int dummy; } ;
struct link_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_NULL ; 
#define  WQL_LINK 129 
 void* WQL_LINK_POISON ; 
#define  WQL_WQS 128 
 int /*<<< orphan*/  WQL_WQS_POISON ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wql_type (struct waitq_link*) ; 

__attribute__((used)) static void wql_poison(struct link_table *table, struct lt_elem *elem)
{
	struct waitq_link *link = (struct waitq_link *)elem;
	(void)table;

	switch (wql_type(link)) {
	case WQL_WQS:
		link->wql_wqs.wql_set = WQL_WQS_POISON;
		break;
	case WQL_LINK:
		link->wql_link.left_setid = WQL_LINK_POISON;
		link->wql_link.right_setid = WQL_LINK_POISON;
		break;
	default:
		break;
	}
#ifdef KEEP_WAITQ_LINK_STATS
	memset(link->sl_alloc_bt, 0, sizeof(link->sl_alloc_bt));
	link->sl_alloc_ts = 0;
	memset(link->sl_mkvalid_bt, 0, sizeof(link->sl_mkvalid_bt));
	link->sl_mkvalid_ts = 0;

	link->sl_alloc_th = THREAD_NULL;
	/* leave the sl_alloc_task in place for debugging */

	link->sl_free_ts = mach_absolute_time();
#endif
}