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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  wql_set; } ;
struct waitq_link {TYPE_1__ wql_wqs; } ;
struct waitq {int dummy; } ;

/* Variables and functions */
 scalar_t__ WQL_WQS ; 
 int WQ_ITERATE_CONTINUE ; 
 scalar_t__ waitq_set_can_prepost (int /*<<< orphan*/ ) ; 
 scalar_t__ wql_type (struct waitq_link*) ; 

__attribute__((used)) static int waitq_prepost_reserve_cb(struct waitq *waitq, void *ctx,
				    struct waitq_link *link)
{
	uint32_t *num = (uint32_t *)ctx;
	(void)waitq;

	/*
	 * In the worst case, we'll have to allocate 2 prepost objects
	 * per waitq set (if the set was already preposted by another
	 * waitq).
	 */
	if (wql_type(link) == WQL_WQS) {
		/*
		 * check to see if the associated waitq actually supports
		 * preposting
		 */
		if (waitq_set_can_prepost(link->wql_wqs.wql_set))
			*num += 2;
	}
	return WQ_ITERATE_CONTINUE;
}