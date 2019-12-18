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
struct ifclassq {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MBUF_SC_UNSPEC ; 
 int /*<<< orphan*/  ifclassq_dequeue_common (struct ifclassq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

errno_t
ifclassq_dequeue(struct ifclassq *ifq, u_int32_t pkt_limit,
    u_int32_t byte_limit, void **head, void **tail,
    u_int32_t *cnt, u_int32_t *len, classq_pkt_type_t *ptype)
{
	return (ifclassq_dequeue_common(ifq, MBUF_SC_UNSPEC, pkt_limit,
	    byte_limit, head, tail, cnt, len, FALSE, ptype));
}