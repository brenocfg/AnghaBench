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
struct tcq_if {int dummy; } ;
typedef  int /*<<< orphan*/  pktsched_pkt_t ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  tcq_dequeue_cl (struct tcq_if*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
tcq_dequeue_tc(struct tcq_if *tif, mbuf_svc_class_t sc, pktsched_pkt_t *pkt)
{
	tcq_dequeue_cl(tif, NULL, sc, pkt);
}