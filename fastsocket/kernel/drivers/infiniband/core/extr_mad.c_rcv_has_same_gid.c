#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
union ib_gid {int /*<<< orphan*/  raw; } ;
typedef  scalar_t__ u8 ;
struct TYPE_11__ {int /*<<< orphan*/  ah; scalar_t__ mad; } ;
struct ib_mad_send_wr_private {TYPE_2__ send_buf; } ;
struct TYPE_18__ {TYPE_8__* grh; struct ib_mad* mad; } ;
struct ib_mad_recv_wc {TYPE_9__ recv_buf; TYPE_4__* wc; } ;
struct TYPE_10__ {scalar_t__ port_num; struct ib_device* device; } ;
struct ib_mad_agent_private {TYPE_1__ agent; } ;
struct ib_mad {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  raw; } ;
struct TYPE_15__ {TYPE_5__ dgid; int /*<<< orphan*/  sgid_index; } ;
struct ib_ah_attr {int ah_flags; int src_path_bits; scalar_t__ dlid; TYPE_6__ grh; } ;
struct TYPE_16__ {int /*<<< orphan*/  raw; } ;
struct TYPE_12__ {int /*<<< orphan*/  raw; } ;
struct TYPE_17__ {TYPE_7__ sgid; TYPE_3__ dgid; } ;
struct TYPE_13__ {int wc_flags; int dlid_path_bits; scalar_t__ slid; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int IB_WC_GRH ; 
 scalar_t__ ib_get_cached_gid (struct ib_device*,scalar_t__,int /*<<< orphan*/ ,union ib_gid*) ; 
 scalar_t__ ib_get_cached_lmc (struct ib_device*,scalar_t__,scalar_t__*) ; 
 scalar_t__ ib_query_ah (int /*<<< orphan*/ ,struct ib_ah_attr*) ; 
 scalar_t__ ib_response_mad (struct ib_mad*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int rcv_has_same_gid(struct ib_mad_agent_private *mad_agent_priv,
				   struct ib_mad_send_wr_private *wr,
				   struct ib_mad_recv_wc *rwc )
{
	struct ib_ah_attr attr;
	u8 send_resp, rcv_resp;
	union ib_gid sgid;
	struct ib_device *device = mad_agent_priv->agent.device;
	u8 port_num = mad_agent_priv->agent.port_num;
	u8 lmc;

	send_resp = ib_response_mad((struct ib_mad *)wr->send_buf.mad);
	rcv_resp = ib_response_mad(rwc->recv_buf.mad);

	if (send_resp == rcv_resp)
		/* both requests, or both responses. GIDs different */
		return 0;

	if (ib_query_ah(wr->send_buf.ah, &attr))
		/* Assume not equal, to avoid false positives. */
		return 0;

	if (!!(attr.ah_flags & IB_AH_GRH) !=
	    !!(rwc->wc->wc_flags & IB_WC_GRH))
		/* one has GID, other does not.  Assume different */
		return 0;

	if (!send_resp && rcv_resp) {
		/* is request/response. */
		if (!(attr.ah_flags & IB_AH_GRH)) {
			if (ib_get_cached_lmc(device, port_num, &lmc))
				return 0;
			return (!lmc || !((attr.src_path_bits ^
					   rwc->wc->dlid_path_bits) &
					  ((1 << lmc) - 1)));
		} else {
			if (ib_get_cached_gid(device, port_num,
					      attr.grh.sgid_index, &sgid))
				return 0;
			return !memcmp(sgid.raw, rwc->recv_buf.grh->dgid.raw,
				       16);
		}
	}

	if (!(attr.ah_flags & IB_AH_GRH))
		return attr.dlid == rwc->wc->slid;
	else
		return !memcmp(attr.grh.dgid.raw, rwc->recv_buf.grh->sgid.raw,
			       16);
}