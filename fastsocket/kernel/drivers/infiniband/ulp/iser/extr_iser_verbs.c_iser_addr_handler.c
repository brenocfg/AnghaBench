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
struct rdma_cm_id {scalar_t__ context; } ;
struct iser_device {int dummy; } ;
struct iser_conn {struct iser_device* device; } ;

/* Variables and functions */
 int iser_connect_error (struct rdma_cm_id*) ; 
 struct iser_device* iser_device_find_by_ib_device (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  iser_err (char*,...) ; 
 int rdma_resolve_route (struct rdma_cm_id*,int) ; 

__attribute__((used)) static int iser_addr_handler(struct rdma_cm_id *cma_id)
{
	struct iser_device *device;
	struct iser_conn   *ib_conn;
	int    ret;

	device = iser_device_find_by_ib_device(cma_id);
	if (!device) {
		iser_err("device lookup/creation failed\n");
		return iser_connect_error(cma_id);
	}

	ib_conn = (struct iser_conn *)cma_id->context;
	ib_conn->device = device;

	ret = rdma_resolve_route(cma_id, 1000);
	if (ret) {
		iser_err("resolve route failed: %d\n", ret);
		return iser_connect_error(cma_id);
	}

	return 0;
}