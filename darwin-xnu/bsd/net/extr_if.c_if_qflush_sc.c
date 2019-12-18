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
typedef  scalar_t__ u_int32_t ;
struct ifclassq {int dummy; } ;
struct ifnet {struct ifclassq if_snd; } ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;

/* Variables and functions */
 scalar_t__ IFCQ_IS_ENABLED (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_PURGE_SC (struct ifclassq*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IFCQ_UNLOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  MBUF_SC_UNSPEC ; 
 scalar_t__ MBUF_VALID_SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 

void
if_qflush_sc(struct ifnet *ifp, mbuf_svc_class_t sc, u_int32_t flow,
    u_int32_t *packets, u_int32_t *bytes, int ifq_locked)
{
	struct ifclassq *ifq = &ifp->if_snd;
	u_int32_t cnt = 0, len = 0;
	u_int32_t a_cnt = 0, a_len = 0;

	VERIFY(sc == MBUF_SC_UNSPEC || MBUF_VALID_SC(sc));
	VERIFY(flow != 0);

	if (!ifq_locked)
		IFCQ_LOCK(ifq);

	if (IFCQ_IS_ENABLED(ifq))
		IFCQ_PURGE_SC(ifq, sc, flow, cnt, len);

	if (!ifq_locked)
		IFCQ_UNLOCK(ifq);

	if (packets != NULL)
		*packets = cnt + a_cnt;
	if (bytes != NULL)
		*bytes = len + a_len;
}