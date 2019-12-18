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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct waitq_link {TYPE_1__ wql_setid; } ;
struct waitq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LT_RESERVED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ get_preemption_level () ; 
 scalar_t__ waitq_wait_possible (int /*<<< orphan*/ ) ; 
 struct waitq_link* wql_alloc_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wql_ensure_free_space () ; 

uint64_t waitq_link_reserve(struct waitq *waitq)
{
	struct waitq_link *link;
	uint64_t reserved_id = 0;

	assert(get_preemption_level() == 0 && waitq_wait_possible(current_thread()));

	/*
	 * We've asserted that the caller can block, so we enforce a
	 * minimum-free table element policy here.
	 */
	wql_ensure_free_space();

	(void)waitq;
	link = wql_alloc_link(LT_RESERVED);
	if (!link)
		return 0;

	reserved_id = link->wql_setid.id;

	return reserved_id;
}