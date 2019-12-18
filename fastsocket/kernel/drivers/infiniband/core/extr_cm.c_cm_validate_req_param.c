#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_cm_req_param {scalar_t__ qp_type; scalar_t__ private_data_len; TYPE_2__* primary_path; TYPE_1__* alternate_path; scalar_t__ private_data; scalar_t__ peer_to_peer; } ;
struct TYPE_4__ {scalar_t__ pkey; scalar_t__ mtu; } ;
struct TYPE_3__ {scalar_t__ pkey; scalar_t__ mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_CM_REQ_PRIVATE_DATA_SIZE ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 scalar_t__ IB_QPT_XRC_INI ; 

__attribute__((used)) static int cm_validate_req_param(struct ib_cm_req_param *param)
{
	/* peer-to-peer not supported */
	if (param->peer_to_peer)
		return -EINVAL;

	if (!param->primary_path)
		return -EINVAL;

	if (param->qp_type != IB_QPT_RC && param->qp_type != IB_QPT_UC &&
	    param->qp_type != IB_QPT_XRC_INI)
		return -EINVAL;

	if (param->private_data &&
	    param->private_data_len > IB_CM_REQ_PRIVATE_DATA_SIZE)
		return -EINVAL;

	if (param->alternate_path &&
	    (param->alternate_path->pkey != param->primary_path->pkey ||
	     param->alternate_path->mtu != param->primary_path->mtu))
		return -EINVAL;

	return 0;
}