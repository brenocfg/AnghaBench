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
struct rdma_ucm_conn_param {int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; } ;
struct rdma_conn_param {int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; } ;
struct TYPE_4__ {scalar_t__ ss_family; } ;
struct TYPE_5__ {TYPE_1__ src_addr; } ;
struct TYPE_6__ {TYPE_2__ addr; } ;
struct rdma_cm_id {TYPE_3__ route; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 

__attribute__((used)) static void ucma_copy_conn_param(struct rdma_cm_id *id,
				 struct rdma_conn_param *dst,
				 struct rdma_ucm_conn_param *src)
{
	dst->private_data = src->private_data;
	dst->private_data_len = src->private_data_len;
	dst->responder_resources =src->responder_resources;
	dst->initiator_depth = src->initiator_depth;
	dst->flow_control = src->flow_control;
	dst->retry_count = src->retry_count;
	dst->rnr_retry_count = src->rnr_retry_count;
	dst->srq = src->srq;
	dst->qp_num = src->qp_num;
	dst->qkey = (id->route.addr.src_addr.ss_family == AF_IB) ? src->qkey : 0;
}