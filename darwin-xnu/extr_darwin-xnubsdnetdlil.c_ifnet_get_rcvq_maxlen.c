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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ifnet {int if_eflags; struct dlil_threading_info* if_inp; } ;
struct dlil_threading_info {int /*<<< orphan*/  input_lck; int /*<<< orphan*/  rcvq_pkts; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int IFEF_RXPOLL ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlimit (int /*<<< orphan*/ *) ; 

errno_t
ifnet_get_rcvq_maxlen(struct ifnet *ifp, u_int32_t *maxqlen)
{
	struct dlil_threading_info *inp;

	if (ifp == NULL || maxqlen == NULL)
		return (EINVAL);
	else if (!(ifp->if_eflags & IFEF_RXPOLL) || ifp->if_inp == NULL)
		return (ENXIO);

	inp = ifp->if_inp;
	lck_mtx_lock(&inp->input_lck);
	*maxqlen = qlimit(&inp->rcvq_pkts);
	lck_mtx_unlock(&inp->input_lck);
	return (0);
}