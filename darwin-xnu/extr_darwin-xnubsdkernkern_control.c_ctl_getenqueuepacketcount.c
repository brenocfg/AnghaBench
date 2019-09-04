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
typedef  scalar_t__ u_int32_t ;
struct TYPE_2__ {struct mbuf* sb_mb; } ;
struct socket {TYPE_1__ so_rcv; } ;
struct mbuf {scalar_t__ m_type; struct mbuf* m_nextpkt; } ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MT_DATA ; 
 scalar_t__ MT_HEADER ; 
 scalar_t__ MT_OOBDATA ; 
 struct socket* kcb_find_socket (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

errno_t
ctl_getenqueuepacketcount(kern_ctl_ref kctlref, u_int32_t unit, u_int32_t *pcnt)
{
	struct socket 	*so;
	u_int32_t cnt;
	struct mbuf *m1;

	if (pcnt == NULL)
		return (EINVAL);

	so = kcb_find_socket(kctlref, unit, NULL);
	if (so == NULL) {
		return (EINVAL);
	}

	cnt = 0;
	m1 = so->so_rcv.sb_mb;
	while (m1 != NULL) {
		if (m1->m_type == MT_DATA ||
		    m1->m_type == MT_HEADER ||
		    m1->m_type == MT_OOBDATA)
			cnt += 1;
		m1 = m1->m_nextpkt;
	}
	*pcnt = cnt;

	socket_unlock(so, 1);

	return (0);
}