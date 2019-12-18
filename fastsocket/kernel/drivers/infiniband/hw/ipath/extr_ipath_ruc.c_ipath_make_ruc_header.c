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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_9__ {int ah_flags; int sl; int dlid; int src_path_bits; int /*<<< orphan*/  grh; } ;
struct TYPE_6__ {int /*<<< orphan*/  grh; } ;
struct TYPE_7__ {TYPE_1__ l; } ;
struct TYPE_8__ {void** lrh; TYPE_2__ u; } ;
struct ipath_qp {int s_cur_size; int s_hdrwords; int remote_qpn; int /*<<< orphan*/  s_pkey_index; TYPE_4__ remote_ah_attr; TYPE_3__ s_hdr; } ;
struct ipath_other_headers {void** bth; } ;
struct ipath_ibdev {TYPE_5__* dd; } ;
struct TYPE_10__ {int ipath_lid; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int IPATH_LRH_BTH ; 
 int IPATH_LRH_GRH ; 
 int SIZE_OF_CRC ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int ipath_get_pkey (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ipath_make_grh (struct ipath_ibdev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ unlikely (int) ; 

void ipath_make_ruc_header(struct ipath_ibdev *dev, struct ipath_qp *qp,
			   struct ipath_other_headers *ohdr,
			   u32 bth0, u32 bth2)
{
	u16 lrh0;
	u32 nwords;
	u32 extra_bytes;

	/* Construct the header. */
	extra_bytes = -qp->s_cur_size & 3;
	nwords = (qp->s_cur_size + extra_bytes) >> 2;
	lrh0 = IPATH_LRH_BTH;
	if (unlikely(qp->remote_ah_attr.ah_flags & IB_AH_GRH)) {
		qp->s_hdrwords += ipath_make_grh(dev, &qp->s_hdr.u.l.grh,
						 &qp->remote_ah_attr.grh,
						 qp->s_hdrwords, nwords);
		lrh0 = IPATH_LRH_GRH;
	}
	lrh0 |= qp->remote_ah_attr.sl << 4;
	qp->s_hdr.lrh[0] = cpu_to_be16(lrh0);
	qp->s_hdr.lrh[1] = cpu_to_be16(qp->remote_ah_attr.dlid);
	qp->s_hdr.lrh[2] = cpu_to_be16(qp->s_hdrwords + nwords + SIZE_OF_CRC);
	qp->s_hdr.lrh[3] = cpu_to_be16(dev->dd->ipath_lid |
				       qp->remote_ah_attr.src_path_bits);
	bth0 |= ipath_get_pkey(dev->dd, qp->s_pkey_index);
	bth0 |= extra_bytes << 20;
	ohdr->bth[0] = cpu_to_be32(bth0 | (1 << 22));
	ohdr->bth[1] = cpu_to_be32(qp->remote_qpn);
	ohdr->bth[2] = cpu_to_be32(bth2);
}