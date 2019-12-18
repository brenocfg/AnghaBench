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
struct mppcbinfo {scalar_t__ mppi_count; int /*<<< orphan*/  mppi_zone; int /*<<< orphan*/  mppi_lock_grp; int /*<<< orphan*/  mppi_pcbs; int /*<<< orphan*/  mppi_lock; } ;
struct mppcb {scalar_t__ mpp_state; int mpp_flags; TYPE_1__* mpp_socket; int /*<<< orphan*/  mpp_lock; struct mppcbinfo* mpp_pcbinfo; } ;
struct TYPE_2__ {scalar_t__ so_usecount; int /*<<< orphan*/ * so_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ MPPCB_STATE_DEAD ; 
 int MPP_ATTACHED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mppcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpp_entry ; 
 int /*<<< orphan*/  mpp_lock_assert_held (struct mppcb*) ; 
 int /*<<< orphan*/  mpp_unlock (struct mppcb*) ; 
 int /*<<< orphan*/  necp_mppcb_dispose (struct mppcb*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct mppcb*) ; 

void
mp_pcbdispose(struct mppcb *mpp)
{
	struct mppcbinfo *mppi = mpp->mpp_pcbinfo;

	VERIFY(mppi != NULL);

	LCK_MTX_ASSERT(&mppi->mppi_lock, LCK_MTX_ASSERT_OWNED);
	mpp_lock_assert_held(mpp);

	VERIFY(mpp->mpp_state == MPPCB_STATE_DEAD);
	VERIFY(mpp->mpp_flags & MPP_ATTACHED);

	mpp->mpp_flags &= ~MPP_ATTACHED;
	TAILQ_REMOVE(&mppi->mppi_pcbs, mpp, mpp_entry);
	VERIFY(mppi->mppi_count != 0);
	mppi->mppi_count--;

	mpp_unlock(mpp);

#if NECP
	necp_mppcb_dispose(mpp);
#endif /* NECP */

	lck_mtx_destroy(&mpp->mpp_lock, mppi->mppi_lock_grp);

	VERIFY(mpp->mpp_socket != NULL);
	VERIFY(mpp->mpp_socket->so_usecount == 0);
	mpp->mpp_socket->so_pcb = NULL;
	mpp->mpp_socket = NULL;

	zfree(mppi->mppi_zone, mpp);
}