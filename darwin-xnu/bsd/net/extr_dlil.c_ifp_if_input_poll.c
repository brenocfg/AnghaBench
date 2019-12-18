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
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
ifp_if_input_poll(struct ifnet *ifp, u_int32_t flags, u_int32_t max_cnt,
    struct mbuf **m_head, struct mbuf **m_tail, u_int32_t *cnt, u_int32_t *len)
{
#pragma unused(ifp, flags, max_cnt)
	if (m_head != NULL)
		*m_head = NULL;
	if (m_tail != NULL)
		*m_tail = NULL;
	if (cnt != NULL)
		*cnt = 0;
	if (len != NULL)
		*len = 0;
}