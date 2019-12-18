#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {unsigned int weight; int bps; int iops; } ;
struct blkio_policy_node {int plid; int /*<<< orphan*/  fileid; TYPE_1__ val; } ;
struct blkio_group {int dummy; } ;
struct blkio_cgroup {unsigned int weight; } ;

/* Variables and functions */
#define  BLKIO_POLICY_PROP 133 
#define  BLKIO_POLICY_THROTL 132 
#define  BLKIO_THROTL_read_bps_device 131 
#define  BLKIO_THROTL_read_iops_device 130 
#define  BLKIO_THROTL_write_bps_device 129 
#define  BLKIO_THROTL_write_iops_device 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  blkio_update_group_bps (struct blkio_group*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkio_update_group_iops (struct blkio_group*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkio_update_group_weight (struct blkio_group*,unsigned int) ; 

__attribute__((used)) static void blkio_update_blkg_policy(struct blkio_cgroup *blkcg,
		struct blkio_group *blkg, struct blkio_policy_node *pn)
{
	unsigned int weight, iops;
	u64 bps;

	switch(pn->plid) {
	case BLKIO_POLICY_PROP:
		weight = pn->val.weight ? pn->val.weight :
				blkcg->weight;
		blkio_update_group_weight(blkg, weight);
		break;
	case BLKIO_POLICY_THROTL:
		switch(pn->fileid) {
		case BLKIO_THROTL_read_bps_device:
		case BLKIO_THROTL_write_bps_device:
			bps = pn->val.bps ? pn->val.bps : (-1);
			blkio_update_group_bps(blkg, bps, pn->fileid);
			break;
		case BLKIO_THROTL_read_iops_device:
		case BLKIO_THROTL_write_iops_device:
			iops = pn->val.iops ? pn->val.iops : (-1);
			blkio_update_group_iops(blkg, iops, pn->fileid);
			break;
		}
		break;
	default:
		BUG();
	}
}