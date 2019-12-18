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
struct sockaddr_in {int dummy; } ;
struct TYPE_4__ {struct iw_cm_id* iw; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct rdma_id_private {TYPE_2__ cm_id; TYPE_1__ id; } ;
struct iw_cm_id {struct sockaddr_in local_addr; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct iw_cm_id*) ; 
 int PTR_ERR (struct iw_cm_id*) ; 
 scalar_t__ cma_src_addr (struct rdma_id_private*) ; 
 int iw_cm_listen (struct iw_cm_id*,int) ; 
 int /*<<< orphan*/  iw_conn_req_handler ; 
 struct iw_cm_id* iw_create_cm_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rdma_id_private*) ; 
 int /*<<< orphan*/  iw_destroy_cm_id (struct iw_cm_id*) ; 

__attribute__((used)) static int cma_iw_listen(struct rdma_id_private *id_priv, int backlog)
{
	int ret;
	struct sockaddr_in *sin;
	struct iw_cm_id	*id;

	id = iw_create_cm_id(id_priv->id.device,
			     iw_conn_req_handler,
			     id_priv);
	if (IS_ERR(id))
		return PTR_ERR(id);

	id_priv->cm_id.iw = id;

	sin = (struct sockaddr_in *) cma_src_addr(id_priv);
	id_priv->cm_id.iw->local_addr = *sin;

	ret = iw_cm_listen(id_priv->cm_id.iw, backlog);

	if (ret) {
		iw_destroy_cm_id(id_priv->cm_id.iw);
		id_priv->cm_id.iw = NULL;
	}

	return ret;
}