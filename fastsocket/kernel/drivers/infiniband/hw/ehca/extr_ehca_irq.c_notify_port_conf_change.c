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
typedef  int /*<<< orphan*/  u16 ;
struct ehca_sma_attr {scalar_t__ sm_sl; scalar_t__ sm_lid; scalar_t__ lid; scalar_t__ lmc; int pkey_tbl_len; int /*<<< orphan*/  pkeys; } ;
struct ehca_shca {TYPE_1__* sport; } ;
struct TYPE_2__ {struct ehca_sma_attr saved_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_LID_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_PKEY_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_SM_CHANGE ; 
 int /*<<< orphan*/  dispatch_port_event (struct ehca_shca*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ehca_query_sma_attr (struct ehca_shca*,int,struct ehca_sma_attr*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void notify_port_conf_change(struct ehca_shca *shca, int port_num)
{
	struct ehca_sma_attr  new_attr;
	struct ehca_sma_attr *old_attr = &shca->sport[port_num - 1].saved_attr;

	ehca_query_sma_attr(shca, port_num, &new_attr);

	if (new_attr.sm_sl  != old_attr->sm_sl ||
	    new_attr.sm_lid != old_attr->sm_lid)
		dispatch_port_event(shca, port_num, IB_EVENT_SM_CHANGE,
				    "SM changed");

	if (new_attr.lid != old_attr->lid ||
	    new_attr.lmc != old_attr->lmc)
		dispatch_port_event(shca, port_num, IB_EVENT_LID_CHANGE,
				    "LID changed");

	if (new_attr.pkey_tbl_len != old_attr->pkey_tbl_len ||
	    memcmp(new_attr.pkeys, old_attr->pkeys,
		   sizeof(u16) * new_attr.pkey_tbl_len))
		dispatch_port_event(shca, port_num, IB_EVENT_PKEY_CHANGE,
				    "P_Key changed");

	*old_attr = new_attr;
}