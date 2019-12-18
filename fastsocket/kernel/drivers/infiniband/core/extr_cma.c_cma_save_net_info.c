#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ss_family; } ;
struct TYPE_7__ {TYPE_1__ src_addr; } ;
struct TYPE_8__ {TYPE_2__ addr; } ;
struct rdma_cm_id {TYPE_3__ route; } ;
struct TYPE_9__ {int /*<<< orphan*/  primary_path; } ;
struct TYPE_10__ {TYPE_4__ req_rcvd; } ;
struct ib_cm_event {struct cma_hdr* private_data; TYPE_5__ param; } ;
struct cma_hdr {scalar_t__ cma_version; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 scalar_t__ CMA_VERSION ; 
 int EINVAL ; 
 int cma_get_ip_ver (struct cma_hdr*) ; 
 int /*<<< orphan*/  cma_save_ib_info (struct rdma_cm_id*,struct rdma_cm_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cma_save_ip4_info (struct rdma_cm_id*,struct rdma_cm_id*,struct cma_hdr*) ; 
 int /*<<< orphan*/  cma_save_ip6_info (struct rdma_cm_id*,struct rdma_cm_id*,struct cma_hdr*) ; 

__attribute__((used)) static int cma_save_net_info(struct rdma_cm_id *id, struct rdma_cm_id *listen_id,
			     struct ib_cm_event *ib_event)
{
	struct cma_hdr *hdr;

	if (listen_id->route.addr.src_addr.ss_family == AF_IB) {
		cma_save_ib_info(id, listen_id, ib_event->param.req_rcvd.primary_path);
		return 0;
	}

	hdr = ib_event->private_data;
	if (hdr->cma_version != CMA_VERSION)
		return -EINVAL;

	switch (cma_get_ip_ver(hdr)) {
	case 4:
		cma_save_ip4_info(id, listen_id, hdr);
		break;
	case 6:
		cma_save_ip6_info(id, listen_id, hdr);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}