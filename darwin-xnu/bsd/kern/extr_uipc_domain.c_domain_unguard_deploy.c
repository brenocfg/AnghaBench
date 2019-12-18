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
typedef  int /*<<< orphan*/  domain_unguard_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  NET_THREAD_HELD_DOMAIN ; 
 int /*<<< orphan*/  domain_proto_mtx ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ net_thread_marks_none ; 
 scalar_t__ net_thread_unmarks_push (int /*<<< orphan*/ ) ; 

domain_unguard_t
domain_unguard_deploy(void)
{
	net_thread_marks_t marks;

	marks = net_thread_unmarks_push(NET_THREAD_HELD_DOMAIN);
	if (marks != net_thread_marks_none) {
		LCK_MTX_ASSERT(&domain_proto_mtx, LCK_MTX_ASSERT_OWNED);
		lck_mtx_unlock(&domain_proto_mtx);
	}
	else
		LCK_MTX_ASSERT(&domain_proto_mtx, LCK_MTX_ASSERT_NOTOWNED);

	return ((domain_unguard_t)(const void*)marks);
}