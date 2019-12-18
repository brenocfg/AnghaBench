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
typedef  int u32 ;
struct qib_ibport {int /*<<< orphan*/ * guids; int /*<<< orphan*/  gid_prefix; } ;
struct TYPE_4__ {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  subnet_prefix; } ;
struct TYPE_5__ {TYPE_1__ global; } ;
struct ib_grh {int /*<<< orphan*/  dgid; TYPE_2__ sgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  next_hdr; int /*<<< orphan*/  paylen; int /*<<< orphan*/  version_tclass_flow; } ;
struct ib_global_route {int traffic_class; int flow_label; int sgid_index; int /*<<< orphan*/  dgid; int /*<<< orphan*/  hop_limit; } ;
struct TYPE_6__ {int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 int IB_GRH_FLOW_SHIFT ; 
 int /*<<< orphan*/  IB_GRH_NEXT_HDR ; 
 int IB_GRH_TCLASS_SHIFT ; 
 int IB_GRH_VERSION ; 
 int IB_GRH_VERSION_SHIFT ; 
 int SIZE_OF_CRC ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 TYPE_3__* ppd_from_ibp (struct qib_ibport*) ; 

u32 qib_make_grh(struct qib_ibport *ibp, struct ib_grh *hdr,
		 struct ib_global_route *grh, u32 hwords, u32 nwords)
{
	hdr->version_tclass_flow =
		cpu_to_be32((IB_GRH_VERSION << IB_GRH_VERSION_SHIFT) |
			    (grh->traffic_class << IB_GRH_TCLASS_SHIFT) |
			    (grh->flow_label << IB_GRH_FLOW_SHIFT));
	hdr->paylen = cpu_to_be16((hwords - 2 + nwords + SIZE_OF_CRC) << 2);
	/* next_hdr is defined by C8-7 in ch. 8.4.1 */
	hdr->next_hdr = IB_GRH_NEXT_HDR;
	hdr->hop_limit = grh->hop_limit;
	/* The SGID is 32-bit aligned. */
	hdr->sgid.global.subnet_prefix = ibp->gid_prefix;
	hdr->sgid.global.interface_id = grh->sgid_index ?
		ibp->guids[grh->sgid_index - 1] : ppd_from_ibp(ibp)->guid;
	hdr->dgid = grh->dgid;

	/* GRH header size in 32-bit words. */
	return sizeof(struct ib_grh) / sizeof(u32);
}