#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_3__ sin_addr; } ;
struct rds_sock {int /*<<< orphan*/  rs_conn_port; int /*<<< orphan*/  rs_conn_addr; int /*<<< orphan*/  rs_bound_port; int /*<<< orphan*/  rs_bound_addr; } ;
struct rds_iw_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct TYPE_5__ {TYPE_1__ addr; } ;
struct rdma_cm_id {TYPE_2__ route; } ;

/* Variables and functions */
 int rds_iw_add_cm_id (struct rds_iw_device*,struct rdma_cm_id*) ; 
 int rds_iw_get_device (struct rds_sock*,struct rds_iw_device**,struct rdma_cm_id**) ; 
 int /*<<< orphan*/  rds_iw_remove_cm_id (struct rds_iw_device*,struct rdma_cm_id*) ; 

int rds_iw_update_cm_id(struct rds_iw_device *rds_iwdev, struct rdma_cm_id *cm_id)
{
	struct sockaddr_in *src_addr, *dst_addr;
	struct rds_iw_device *rds_iwdev_old;
	struct rds_sock rs;
	struct rdma_cm_id *pcm_id;
	int rc;

	src_addr = (struct sockaddr_in *)&cm_id->route.addr.src_addr;
	dst_addr = (struct sockaddr_in *)&cm_id->route.addr.dst_addr;

	rs.rs_bound_addr = src_addr->sin_addr.s_addr;
	rs.rs_bound_port = src_addr->sin_port;
	rs.rs_conn_addr = dst_addr->sin_addr.s_addr;
	rs.rs_conn_port = dst_addr->sin_port;

	rc = rds_iw_get_device(&rs, &rds_iwdev_old, &pcm_id);
	if (rc)
		rds_iw_remove_cm_id(rds_iwdev, cm_id);

	return rds_iw_add_cm_id(rds_iwdev, cm_id);
}