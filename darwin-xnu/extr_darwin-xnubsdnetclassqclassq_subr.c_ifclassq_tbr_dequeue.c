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
struct ifclassq {int dummy; } ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MBUF_SC_UNSPEC ; 
 void* ifclassq_tbr_dequeue_common (struct ifclassq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void *
ifclassq_tbr_dequeue(struct ifclassq *ifq, classq_pkt_type_t *ptype)
{
	return (ifclassq_tbr_dequeue_common(ifq, MBUF_SC_UNSPEC, FALSE, ptype));
}