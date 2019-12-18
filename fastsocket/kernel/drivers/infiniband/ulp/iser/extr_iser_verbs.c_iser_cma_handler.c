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
struct rdma_cm_id {int /*<<< orphan*/  context; } ;
struct rdma_cm_event {int event; int /*<<< orphan*/  status; } ;

/* Variables and functions */
#define  RDMA_CM_EVENT_ADDR_CHANGE 138 
#define  RDMA_CM_EVENT_ADDR_ERROR 137 
#define  RDMA_CM_EVENT_ADDR_RESOLVED 136 
#define  RDMA_CM_EVENT_CONNECT_ERROR 135 
#define  RDMA_CM_EVENT_DEVICE_REMOVAL 134 
#define  RDMA_CM_EVENT_DISCONNECTED 133 
#define  RDMA_CM_EVENT_ESTABLISHED 132 
#define  RDMA_CM_EVENT_REJECTED 131 
#define  RDMA_CM_EVENT_ROUTE_ERROR 130 
#define  RDMA_CM_EVENT_ROUTE_RESOLVED 129 
#define  RDMA_CM_EVENT_UNREACHABLE 128 
 int iser_addr_handler (struct rdma_cm_id*) ; 
 int iser_connect_error (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  iser_connected_handler (struct rdma_cm_id*) ; 
 int iser_disconnected_handler (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 
 int /*<<< orphan*/  iser_info (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rdma_cm_id*) ; 
 int iser_route_handler (struct rdma_cm_id*) ; 

__attribute__((used)) static int iser_cma_handler(struct rdma_cm_id *cma_id, struct rdma_cm_event *event)
{
	int ret = 0;

	iser_info("event %d status %d conn %p id %p\n",
		  event->event, event->status, cma_id->context, cma_id);

	switch (event->event) {
	case RDMA_CM_EVENT_ADDR_RESOLVED:
		ret = iser_addr_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ROUTE_RESOLVED:
		ret = iser_route_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ESTABLISHED:
		iser_connected_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ADDR_ERROR:
	case RDMA_CM_EVENT_ROUTE_ERROR:
	case RDMA_CM_EVENT_CONNECT_ERROR:
	case RDMA_CM_EVENT_UNREACHABLE:
	case RDMA_CM_EVENT_REJECTED:
		ret = iser_connect_error(cma_id);
		break;
	case RDMA_CM_EVENT_DISCONNECTED:
	case RDMA_CM_EVENT_DEVICE_REMOVAL:
	case RDMA_CM_EVENT_ADDR_CHANGE:
		ret = iser_disconnected_handler(cma_id);
		break;
	default:
		iser_err("Unexpected RDMA CM event (%d)\n", event->event);
		break;
	}
	return ret;
}