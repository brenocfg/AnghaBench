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
struct ehea_port_res {int /*<<< orphan*/  rq2_skba; } ;

/* Variables and functions */
 scalar_t__ EHEA_RQ2_PKT_SIZE ; 
 int /*<<< orphan*/  EHEA_RWQE2_TYPE ; 
 scalar_t__ NET_IP_ALIGN ; 
 int ehea_refill_rq_def (struct ehea_port_res*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ehea_refill_rq2(struct ehea_port_res *pr, int nr_of_wqes)
{
	return ehea_refill_rq_def(pr, &pr->rq2_skba, 2,
				  nr_of_wqes, EHEA_RWQE2_TYPE,
				  EHEA_RQ2_PKT_SIZE + NET_IP_ALIGN);
}