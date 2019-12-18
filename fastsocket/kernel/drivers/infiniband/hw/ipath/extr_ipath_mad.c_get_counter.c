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
typedef  int /*<<< orphan*/  u64 ;
struct ipath_ibdev {int /*<<< orphan*/  ipath_xmit_wait; int /*<<< orphan*/  dd; int /*<<< orphan*/  ipath_rpkts; int /*<<< orphan*/  ipath_spkts; int /*<<< orphan*/  ipath_rword; int /*<<< orphan*/  ipath_sword; } ;
struct ipath_cregs {int /*<<< orphan*/  cr_psxmitwaitcount; int /*<<< orphan*/  cr_psrcvpktscount; int /*<<< orphan*/  cr_psxmitpktscount; int /*<<< orphan*/  cr_psrcvdatacount; int /*<<< orphan*/  cr_psxmitdatacount; } ;
typedef  int __be16 ;

/* Variables and functions */
#define  IB_PMA_PORT_RCV_DATA 132 
#define  IB_PMA_PORT_RCV_PKTS 131 
#define  IB_PMA_PORT_XMIT_DATA 130 
#define  IB_PMA_PORT_XMIT_PKTS 129 
#define  IB_PMA_PORT_XMIT_WAIT 128 
 int /*<<< orphan*/  ipath_read_creg32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 get_counter(struct ipath_ibdev *dev,
		       struct ipath_cregs const *crp,
		       __be16 sel)
{
	u64 ret;

	switch (sel) {
	case IB_PMA_PORT_XMIT_DATA:
		ret = (crp->cr_psxmitdatacount) ?
			ipath_read_creg32(dev->dd, crp->cr_psxmitdatacount) :
			dev->ipath_sword;
		break;
	case IB_PMA_PORT_RCV_DATA:
		ret = (crp->cr_psrcvdatacount) ?
			ipath_read_creg32(dev->dd, crp->cr_psrcvdatacount) :
			dev->ipath_rword;
		break;
	case IB_PMA_PORT_XMIT_PKTS:
		ret = (crp->cr_psxmitpktscount) ?
			ipath_read_creg32(dev->dd, crp->cr_psxmitpktscount) :
			dev->ipath_spkts;
		break;
	case IB_PMA_PORT_RCV_PKTS:
		ret = (crp->cr_psrcvpktscount) ?
			ipath_read_creg32(dev->dd, crp->cr_psrcvpktscount) :
			dev->ipath_rpkts;
		break;
	case IB_PMA_PORT_XMIT_WAIT:
		ret = (crp->cr_psxmitwaitcount) ?
			ipath_read_creg32(dev->dd, crp->cr_psxmitwaitcount) :
			dev->ipath_xmit_wait;
		break;
	default:
		ret = 0;
	}

	return ret;
}