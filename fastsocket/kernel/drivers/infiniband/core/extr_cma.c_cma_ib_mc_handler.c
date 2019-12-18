#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* event_handler ) (TYPE_3__*,struct rdma_cm_event*) ;int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; scalar_t__ qp; } ;
struct rdma_id_private {int /*<<< orphan*/  handler_mutex; TYPE_3__ id; int /*<<< orphan*/  qp_mutex; } ;
struct TYPE_6__ {int qp_num; int /*<<< orphan*/  qkey; int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  private_data; } ;
struct TYPE_7__ {TYPE_1__ ud; } ;
struct rdma_cm_event {int status; int /*<<< orphan*/  event; TYPE_2__ param; } ;
struct TYPE_9__ {int /*<<< orphan*/  qkey; int /*<<< orphan*/  mlid; int /*<<< orphan*/  mgid; } ;
struct ib_sa_multicast {TYPE_5__ rec; struct cma_multicast* context; } ;
struct cma_multicast {int /*<<< orphan*/  context; struct rdma_id_private* id_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_CM_ADDR_BOUND ; 
 int /*<<< orphan*/  RDMA_CM_ADDR_RESOLVED ; 
 int /*<<< orphan*/  RDMA_CM_DESTROYING ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_MULTICAST_ERROR ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_MULTICAST_JOIN ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cma_disable_callback (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cma_exch (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int cma_set_qkey (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int ib_attach_mcast (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_init_ah_from_mcmember (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rdma_cm_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_3__*) ; 
 int stub1 (TYPE_3__*,struct rdma_cm_event*) ; 

__attribute__((used)) static int cma_ib_mc_handler(int status, struct ib_sa_multicast *multicast)
{
	struct rdma_id_private *id_priv;
	struct cma_multicast *mc = multicast->context;
	struct rdma_cm_event event;
	int ret;

	id_priv = mc->id_priv;
	if (cma_disable_callback(id_priv, RDMA_CM_ADDR_BOUND) &&
	    cma_disable_callback(id_priv, RDMA_CM_ADDR_RESOLVED))
		return 0;

	if (!status)
		status = cma_set_qkey(id_priv, be32_to_cpu(multicast->rec.qkey));
	mutex_lock(&id_priv->qp_mutex);
	if (!status && id_priv->id.qp)
		status = ib_attach_mcast(id_priv->id.qp, &multicast->rec.mgid,
					 be16_to_cpu(multicast->rec.mlid));
	mutex_unlock(&id_priv->qp_mutex);

	memset(&event, 0, sizeof event);
	event.status = status;
	event.param.ud.private_data = mc->context;
	if (!status) {
		event.event = RDMA_CM_EVENT_MULTICAST_JOIN;
		ib_init_ah_from_mcmember(id_priv->id.device,
					 id_priv->id.port_num, &multicast->rec,
					 &event.param.ud.ah_attr);
		event.param.ud.qp_num = 0xFFFFFF;
		event.param.ud.qkey = be32_to_cpu(multicast->rec.qkey);
	} else
		event.event = RDMA_CM_EVENT_MULTICAST_ERROR;

	ret = id_priv->id.event_handler(&id_priv->id, &event);
	if (ret) {
		cma_exch(id_priv, RDMA_CM_DESTROYING);
		mutex_unlock(&id_priv->handler_mutex);
		rdma_destroy_id(&id_priv->id);
		return 0;
	}

	mutex_unlock(&id_priv->handler_mutex);
	return 0;
}