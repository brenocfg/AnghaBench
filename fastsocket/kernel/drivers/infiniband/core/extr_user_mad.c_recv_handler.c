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
struct TYPE_7__ {int grh_present; void* flow_label; int /*<<< orphan*/  gid; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  gid_index; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  lid; void* qpn; scalar_t__ length; scalar_t__ status; } ;
struct TYPE_8__ {TYPE_2__ hdr; } ;
struct ib_umad_packet {TYPE_3__ mad; struct ib_mad_recv_wc* recv_wc; scalar_t__ length; } ;
struct ib_umad_file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  grh; } ;
struct ib_mad_recv_wc {TYPE_1__ recv_buf; TYPE_5__* wc; scalar_t__ mad_len; } ;
struct ib_mad_agent {int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; struct ib_umad_file* context; } ;
struct TYPE_9__ {int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; } ;
struct ib_ah_attr {TYPE_4__ grh; } ;
struct TYPE_10__ {scalar_t__ status; int wc_flags; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  dlid_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; int /*<<< orphan*/  src_qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_WC_GRH ; 
 scalar_t__ IB_WC_SUCCESS ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ hdr_size (struct ib_umad_file*) ; 
 int /*<<< orphan*/  ib_free_recv_mad (struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  ib_init_ah_from_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,struct ib_ah_attr*) ; 
 int /*<<< orphan*/  kfree (struct ib_umad_packet*) ; 
 struct ib_umad_packet* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ queue_packet (struct ib_umad_file*,struct ib_mad_agent*,struct ib_umad_packet*) ; 

__attribute__((used)) static void recv_handler(struct ib_mad_agent *agent,
			 struct ib_mad_recv_wc *mad_recv_wc)
{
	struct ib_umad_file *file = agent->context;
	struct ib_umad_packet *packet;

	if (mad_recv_wc->wc->status != IB_WC_SUCCESS)
		goto err1;

	packet = kzalloc(sizeof *packet, GFP_KERNEL);
	if (!packet)
		goto err1;

	packet->length = mad_recv_wc->mad_len;
	packet->recv_wc = mad_recv_wc;

	packet->mad.hdr.status	   = 0;
	packet->mad.hdr.length	   = hdr_size(file) + mad_recv_wc->mad_len;
	packet->mad.hdr.qpn	   = cpu_to_be32(mad_recv_wc->wc->src_qp);
	packet->mad.hdr.lid	   = cpu_to_be16(mad_recv_wc->wc->slid);
	packet->mad.hdr.sl	   = mad_recv_wc->wc->sl;
	packet->mad.hdr.path_bits  = mad_recv_wc->wc->dlid_path_bits;
	packet->mad.hdr.pkey_index = mad_recv_wc->wc->pkey_index;
	packet->mad.hdr.grh_present = !!(mad_recv_wc->wc->wc_flags & IB_WC_GRH);
	if (packet->mad.hdr.grh_present) {
		struct ib_ah_attr ah_attr;

		ib_init_ah_from_wc(agent->device, agent->port_num,
				   mad_recv_wc->wc, mad_recv_wc->recv_buf.grh,
				   &ah_attr);

		packet->mad.hdr.gid_index = ah_attr.grh.sgid_index;
		packet->mad.hdr.hop_limit = ah_attr.grh.hop_limit;
		packet->mad.hdr.traffic_class = ah_attr.grh.traffic_class;
		memcpy(packet->mad.hdr.gid, &ah_attr.grh.dgid, 16);
		packet->mad.hdr.flow_label = cpu_to_be32(ah_attr.grh.flow_label);
	}

	if (queue_packet(file, agent, packet))
		goto err2;
	return;

err2:
	kfree(packet);
err1:
	ib_free_recv_mad(mad_recv_wc);
}