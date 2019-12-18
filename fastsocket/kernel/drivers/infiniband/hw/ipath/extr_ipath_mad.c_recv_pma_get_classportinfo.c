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
struct ib_smp {int dummy; } ;
struct TYPE_2__ {scalar_t__ attr_mod; int /*<<< orphan*/  status; } ;
struct ib_pma_mad {TYPE_1__ mad_hdr; scalar_t__ data; } ;
struct ib_class_port_info {int base_version; int class_version; int resp_time_value; int /*<<< orphan*/  capability_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int reply (struct ib_smp*) ; 

__attribute__((used)) static int recv_pma_get_classportinfo(struct ib_pma_mad *pmp)
{
	struct ib_class_port_info *p =
		(struct ib_class_port_info *)pmp->data;

	memset(pmp->data, 0, sizeof(pmp->data));

	if (pmp->mad_hdr.attr_mod != 0)
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;

	/* Indicate AllPortSelect is valid (only one port anyway) */
	p->capability_mask = cpu_to_be16(1 << 8);
	p->base_version = 1;
	p->class_version = 1;
	/*
	 * Expected response time is 4.096 usec. * 2^18 == 1.073741824
	 * sec.
	 */
	p->resp_time_value = 18;

	return reply((struct ib_smp *) pmp);
}