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
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct rdma_cm_id {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ node_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  IB_QPT_RC ; 
 scalar_t__ IS_ERR (struct rdma_cm_id*) ; 
 int PTR_ERR (struct rdma_cm_id*) ; 
 scalar_t__ RDMA_NODE_RNIC ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int rdma_bind_addr (struct rdma_cm_id*,struct sockaddr*) ; 
 struct rdma_cm_id* rdma_create_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int rds_iw_laddr_check(__be32 addr)
{
	int ret;
	struct rdma_cm_id *cm_id;
	struct sockaddr_in sin;

	/* Create a CMA ID and try to bind it. This catches both
	 * IB and iWARP capable NICs.
	 */
	cm_id = rdma_create_id(NULL, NULL, RDMA_PS_TCP, IB_QPT_RC);
	if (IS_ERR(cm_id))
		return PTR_ERR(cm_id);

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = addr;

	/* rdma_bind_addr will only succeed for IB & iWARP devices */
	ret = rdma_bind_addr(cm_id, (struct sockaddr *)&sin);
	/* due to this, we will claim to support IB devices unless we
	   check node_type. */
	if (ret || cm_id->device->node_type != RDMA_NODE_RNIC)
		ret = -EADDRNOTAVAIL;

	rdsdebug("addr %pI4 ret %d node type %d\n",
		&addr, ret,
		cm_id->device ? cm_id->device->node_type : -1);

	rdma_destroy_id(cm_id);

	return ret;
}