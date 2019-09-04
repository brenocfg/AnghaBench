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
struct TYPE_2__ {void* wqp_wq_id; void* wqp_next_id; } ;
struct wq_prepost {TYPE_1__ wqp_post; } ;
struct lt_elem {int dummy; } ;
struct link_table {int dummy; } ;

/* Variables and functions */
#define  WQP_POST 129 
 void* WQP_POST_POISON ; 
#define  WQP_WQ 128 
 int wqp_type (struct wq_prepost*) ; 

__attribute__((used)) static void wqp_poison(struct link_table *table, struct lt_elem *elem)
{
	struct wq_prepost *wqp = (struct wq_prepost *)elem;
	(void)table;

	switch (wqp_type(wqp)) {
	case WQP_WQ:
		break;
	case WQP_POST:
		wqp->wqp_post.wqp_next_id = WQP_POST_POISON;
		wqp->wqp_post.wqp_wq_id = WQP_POST_POISON;
		break;
	default:
		break;
	}
}