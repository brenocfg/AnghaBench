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
struct iser_device {int dummy; } ;
struct iser_conn {scalar_t__ state; int /*<<< orphan*/  ep; int /*<<< orphan*/ * cma_id; struct iser_device* device; int /*<<< orphan*/  conn_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  connlist_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ ISER_CONN_DOWN ; 
 TYPE_1__ ig ; 
 int /*<<< orphan*/  iscsi_destroy_endpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_device_try_release (struct iser_device*) ; 
 int /*<<< orphan*/  iser_free_ib_conn_res (struct iser_conn*) ; 
 int /*<<< orphan*/  iser_free_rx_descriptors (struct iser_conn*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iser_conn_release(struct iser_conn *ib_conn, int can_destroy_id)
{
	struct iser_device  *device = ib_conn->device;

	BUG_ON(ib_conn->state != ISER_CONN_DOWN);

	mutex_lock(&ig.connlist_mutex);
	list_del(&ib_conn->conn_list);
	mutex_unlock(&ig.connlist_mutex);
	iser_free_rx_descriptors(ib_conn);
	iser_free_ib_conn_res(ib_conn);
	ib_conn->device = NULL;
	/* on EVENT_ADDR_ERROR there's no device yet for this conn */
	if (device != NULL)
		iser_device_try_release(device);
	/* if cma handler context, the caller actually destroy the id */
	if (ib_conn->cma_id != NULL && can_destroy_id) {
		rdma_destroy_id(ib_conn->cma_id);
		ib_conn->cma_id = NULL;
	}
	iscsi_destroy_endpoint(ib_conn->ep);
}