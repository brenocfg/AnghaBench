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
struct ib_device {int phys_port_cnt; } ;
struct TYPE_2__ {scalar_t__ sgid_index; } ;
struct ib_ah_attr {scalar_t__ dlid; int ah_flags; int port_num; scalar_t__ static_rate; int sl; TYPE_1__ grh; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_AH_GRH ; 
 scalar_t__ IB_RATE_PORT_CURRENT ; 
 scalar_t__ QIB_GUIDS_PER_PORT ; 
 scalar_t__ QIB_MULTICAST_LID_BASE ; 
 scalar_t__ QIB_PERMISSIVE_LID ; 
 scalar_t__ ib_rate_to_mult (scalar_t__) ; 

int qib_check_ah(struct ib_device *ibdev, struct ib_ah_attr *ah_attr)
{
	/* A multicast address requires a GRH (see ch. 8.4.1). */
	if (ah_attr->dlid >= QIB_MULTICAST_LID_BASE &&
	    ah_attr->dlid != QIB_PERMISSIVE_LID &&
	    !(ah_attr->ah_flags & IB_AH_GRH))
		goto bail;
	if ((ah_attr->ah_flags & IB_AH_GRH) &&
	    ah_attr->grh.sgid_index >= QIB_GUIDS_PER_PORT)
		goto bail;
	if (ah_attr->dlid == 0)
		goto bail;
	if (ah_attr->port_num < 1 ||
	    ah_attr->port_num > ibdev->phys_port_cnt)
		goto bail;
	if (ah_attr->static_rate != IB_RATE_PORT_CURRENT &&
	    ib_rate_to_mult(ah_attr->static_rate) < 0)
		goto bail;
	if (ah_attr->sl > 15)
		goto bail;
	return 0;
bail:
	return -EINVAL;
}