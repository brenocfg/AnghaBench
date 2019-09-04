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
struct ifnet_poll_params {int /*<<< orphan*/  interval_time; int /*<<< orphan*/  bytes_hiwat; int /*<<< orphan*/  bytes_lowat; int /*<<< orphan*/  packets_hiwat; int /*<<< orphan*/  packets_lowat; int /*<<< orphan*/  packets_limit; } ;
struct ifnet {int if_eflags; struct dlil_threading_info* if_inp; } ;
struct dlil_threading_info {int /*<<< orphan*/  input_lck; int /*<<< orphan*/  rxpoll_ival; int /*<<< orphan*/  rxpoll_bhiwat; int /*<<< orphan*/  rxpoll_blowat; int /*<<< orphan*/  rxpoll_phiwat; int /*<<< orphan*/  rxpoll_plowat; int /*<<< orphan*/  rxpoll_plim; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int IFEF_RXPOLL ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (struct ifnet_poll_params*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

errno_t
dlil_rxpoll_get_params(struct ifnet *ifp, struct ifnet_poll_params *p)
{
	struct dlil_threading_info *inp;

	VERIFY(ifp != NULL && p != NULL);
	if (!(ifp->if_eflags & IFEF_RXPOLL) || (inp = ifp->if_inp) == NULL)
		return (ENXIO);

	bzero(p, sizeof (*p));

	lck_mtx_lock(&inp->input_lck);
	p->packets_limit = inp->rxpoll_plim;
	p->packets_lowat = inp->rxpoll_plowat;
	p->packets_hiwat = inp->rxpoll_phiwat;
	p->bytes_lowat = inp->rxpoll_blowat;
	p->bytes_hiwat = inp->rxpoll_bhiwat;
	p->interval_time = inp->rxpoll_ival;
	lck_mtx_unlock(&inp->input_lck);

	return (0);
}