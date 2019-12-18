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
struct socket {struct mppcb* so_pcb; } ;
struct mppcbinfo {int /*<<< orphan*/  mppi_lock; int /*<<< orphan*/  mppi_count; int /*<<< orphan*/  mppi_pcbs; int /*<<< orphan*/  mppi_zone; int /*<<< orphan*/  mppi_lock_grp; int /*<<< orphan*/  mppi_lock_attr; int /*<<< orphan*/  mppi_size; } ;
struct mppcb {int /*<<< orphan*/  mpp_flags; int /*<<< orphan*/  mpp_lock; struct socket* mpp_socket; int /*<<< orphan*/  mpp_state; struct mppcbinfo* mpp_pcbinfo; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  MPPCB_STATE_INUSE ; 
 int /*<<< orphan*/  MPP_ATTACHED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mppcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct mppcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpp_entry ; 
 int /*<<< orphan*/ * mpsotomppcb (struct socket*) ; 
 int mptcp_sescreate (struct mppcb*) ; 
 struct mppcb* zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct mppcb*) ; 

int
mp_pcballoc(struct socket *so, struct mppcbinfo *mppi)
{
	struct mppcb *mpp = NULL;
	int error;

	VERIFY(mpsotomppcb(so) == NULL);

	mpp = zalloc(mppi->mppi_zone);
	if (mpp == NULL) {
		return (ENOBUFS);
	}

	bzero(mpp, mppi->mppi_size);
	lck_mtx_init(&mpp->mpp_lock, mppi->mppi_lock_grp, mppi->mppi_lock_attr);
	mpp->mpp_pcbinfo = mppi;
	mpp->mpp_state = MPPCB_STATE_INUSE;
	mpp->mpp_socket = so;
	so->so_pcb = mpp;

	error = mptcp_sescreate(mpp);
	if (error) {
		lck_mtx_destroy(&mpp->mpp_lock, mppi->mppi_lock_grp);
		zfree(mppi->mppi_zone, mpp);
		return (error);
	}

	lck_mtx_lock(&mppi->mppi_lock);
	mpp->mpp_flags |= MPP_ATTACHED;
	TAILQ_INSERT_TAIL(&mppi->mppi_pcbs, mpp, mpp_entry);
	mppi->mppi_count++;
	lck_mtx_unlock(&mppi->mppi_lock);

	return (0);
}