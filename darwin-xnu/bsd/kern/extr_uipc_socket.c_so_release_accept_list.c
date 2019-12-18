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
struct socket {int /*<<< orphan*/  so_incomp; int /*<<< orphan*/  so_flags1; TYPE_1__* so_proto; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* pr_getlock ) (struct socket*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  SOF1_ACCEPT_LIST_HELD ; 
 int /*<<< orphan*/ * stub1 (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
so_release_accept_list(struct socket *head)
{
	if (head->so_proto->pr_getlock != NULL) {
		lck_mtx_t *mutex_held;

		mutex_held = (*head->so_proto->pr_getlock)(head, 0);
		LCK_MTX_ASSERT(mutex_held, LCK_MTX_ASSERT_OWNED);

		head->so_flags1 &= ~SOF1_ACCEPT_LIST_HELD;
		wakeup((caddr_t)&head->so_incomp);
	}
}