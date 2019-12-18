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
typedef  int u_int32_t ;
struct mbuf {int dummy; } ;
struct ifnet {int if_eflags; scalar_t__ if_output_sched_model; int /*<<< orphan*/  if_snd; } ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  scalar_t__ classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSQ_DEQUEUE_MAX_PKT_LIMIT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int IFEF_TXSTART ; 
 scalar_t__ IFNET_SCHED_MODEL_MAX ; 
 scalar_t__ QP_MBUF ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ifclassq_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void**,void**,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  ifnet_decr_iorefcnt (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_is_attached (struct ifnet*,int) ; 

errno_t
ifnet_dequeue_multi_bytes(struct ifnet *ifp, u_int32_t byte_limit,
    struct mbuf **head, struct mbuf **tail, u_int32_t *cnt, u_int32_t *len)
{
	errno_t rc;
	classq_pkt_type_t ptype;
	if (ifp == NULL || head == NULL || byte_limit < 1)
		return (EINVAL);
	else if (!(ifp->if_eflags & IFEF_TXSTART) ||
	    ifp->if_output_sched_model >= IFNET_SCHED_MODEL_MAX)
		return (ENXIO);
	if (!ifnet_is_attached(ifp, 1))
		return (ENXIO);

	rc = ifclassq_dequeue(&ifp->if_snd, CLASSQ_DEQUEUE_MAX_PKT_LIMIT,
	    byte_limit, (void **)head, (void **)tail, cnt, len, &ptype);
	VERIFY((*head == NULL) || (ptype == QP_MBUF));
	ifnet_decr_iorefcnt(ifp);
	return (rc);
}