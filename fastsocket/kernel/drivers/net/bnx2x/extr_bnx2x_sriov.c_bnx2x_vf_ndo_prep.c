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
struct pf_vf_bulletin_content {int dummy; } ;
struct bnx2x_virtf {int dummy; } ;
struct bnx2x {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,...) ; 
 int BNX2X_NR_VIRTFN (struct bnx2x*) ; 
 scalar_t__ BNX2X_STATE_OPEN ; 
 struct bnx2x_virtf* BP_VF (struct bnx2x*,int) ; 
 struct pf_vf_bulletin_content* BP_VF_BULLETIN (struct bnx2x*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_SRIOV (struct bnx2x*) ; 

__attribute__((used)) static int bnx2x_vf_ndo_prep(struct bnx2x *bp, int vfidx,
			     struct bnx2x_virtf **vf,
			     struct pf_vf_bulletin_content **bulletin)
{
	if (bp->state != BNX2X_STATE_OPEN) {
		BNX2X_ERR("vf ndo called though PF is down\n");
		return -EINVAL;
	}

	if (!IS_SRIOV(bp)) {
		BNX2X_ERR("vf ndo called though sriov is disabled\n");
		return -EINVAL;
	}

	if (vfidx >= BNX2X_NR_VIRTFN(bp)) {
		BNX2X_ERR("vf ndo called for uninitialized VF. vfidx was %d BNX2X_NR_VIRTFN was %d\n",
			  vfidx, BNX2X_NR_VIRTFN(bp));
		return -EINVAL;
	}

	/* init members */
	*vf = BP_VF(bp, vfidx);
	*bulletin = BP_VF_BULLETIN(bp, vfidx);

	if (!*vf) {
		BNX2X_ERR("vf ndo called but vf was null. vfidx was %d\n",
			  vfidx);
		return -EINVAL;
	}

	if (!*bulletin) {
		BNX2X_ERR("vf ndo called but Bulletin Board struct is null. vfidx was %d\n",
			  vfidx);
		return -EINVAL;
	}

	return 0;
}