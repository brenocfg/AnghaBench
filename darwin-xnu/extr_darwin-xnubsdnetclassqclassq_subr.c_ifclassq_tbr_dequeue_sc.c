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
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 void* ifclassq_tbr_dequeue_common (struct ifclassq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void *
ifclassq_tbr_dequeue_sc(struct ifclassq *ifq, mbuf_svc_class_t sc,
    classq_pkt_type_t *ptype)
{
	return (ifclassq_tbr_dequeue_common(ifq, sc, TRUE, ptype));
}