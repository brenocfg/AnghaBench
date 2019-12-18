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
struct TYPE_2__ {int /*<<< orphan*/  iops; int /*<<< orphan*/  bps; int /*<<< orphan*/  weight; } ;
struct blkio_policy_node {int plid; TYPE_1__ val; int /*<<< orphan*/  fileid; } ;

/* Variables and functions */
#define  BLKIO_POLICY_PROP 133 
#define  BLKIO_POLICY_THROTL 132 
#define  BLKIO_THROTL_read_bps_device 131 
#define  BLKIO_THROTL_read_iops_device 130 
#define  BLKIO_THROTL_write_bps_device 129 
#define  BLKIO_THROTL_write_iops_device 128 
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static void blkio_update_policy_rule(struct blkio_policy_node *oldpn,
					struct blkio_policy_node *newpn)
{
	switch(oldpn->plid) {
	case BLKIO_POLICY_PROP:
		oldpn->val.weight = newpn->val.weight;
		break;
	case BLKIO_POLICY_THROTL:
		switch(newpn->fileid) {
		case BLKIO_THROTL_read_bps_device:
		case BLKIO_THROTL_write_bps_device:
			oldpn->val.bps = newpn->val.bps;
			break;
		case BLKIO_THROTL_read_iops_device:
		case BLKIO_THROTL_write_iops_device:
			oldpn->val.iops = newpn->val.iops;
		}
		break;
	default:
		BUG();
	}
}