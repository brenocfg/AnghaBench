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
typedef  scalar_t__ net_thread_marks_t ;
typedef  scalar_t__ domain_unguard_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  domain_proto_mtx ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ net_thread_marks_none ; 
 int /*<<< orphan*/  net_thread_unmarks_pop (scalar_t__) ; 

void
domain_unguard_release(domain_unguard_t unguard)
{
	net_thread_marks_t marks = (net_thread_marks_t)(const void*)unguard;

	if (marks != net_thread_marks_none) {
		LCK_MTX_ASSERT(&domain_proto_mtx, LCK_MTX_ASSERT_NOTOWNED);
		lck_mtx_lock(&domain_proto_mtx);
		net_thread_unmarks_pop(marks);
	}
	else
		LCK_MTX_ASSERT(&domain_proto_mtx, LCK_MTX_ASSERT_OWNED);
}