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
struct ipath_ibdev {TYPE_3__* dd; int /*<<< orphan*/  gid_prefix; } ;
struct TYPE_4__ {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  subnet_prefix; } ;
struct TYPE_5__ {TYPE_1__ global; } ;
struct ib_grh {int next_hdr; int /*<<< orphan*/  dgid; TYPE_2__ sgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  paylen; int /*<<< orphan*/  version_tclass_flow; } ;
struct ib_global_route {int traffic_class; int flow_label; int /*<<< orphan*/  dgid; int /*<<< orphan*/  hop_limit; } ;
struct TYPE_6__ {int /*<<< orphan*/  ipath_guid; } ;

/* Variables and functions */
 int SIZE_OF_CRC ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

u32 ipath_make_grh(struct ipath_ibdev *dev, struct ib_grh *hdr,
		   struct ib_global_route *grh, u32 hwords, u32 nwords)
{
	hdr->version_tclass_flow =
		cpu_to_be32((6 << 28) |
			    (grh->traffic_class << 20) |
			    grh->flow_label);
	hdr->paylen = cpu_to_be16((hwords - 2 + nwords + SIZE_OF_CRC) << 2);
	/* next_hdr is defined by C8-7 in ch. 8.4.1 */
	hdr->next_hdr = 0x1B;
	hdr->hop_limit = grh->hop_limit;
	/* The SGID is 32-bit aligned. */
	hdr->sgid.global.subnet_prefix = dev->gid_prefix;
	hdr->sgid.global.interface_id = dev->dd->ipath_guid;
	hdr->dgid = grh->dgid;

	/* GRH header size in 32-bit words. */
	return sizeof(struct ib_grh) / sizeof(u32);
}