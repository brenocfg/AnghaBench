#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct brcms_hardware {struct brcms_c_info* wlc; } ;
struct brcms_c_info {TYPE_1__* band; } ;
struct TYPE_3__ {int /*<<< orphan*/  phyrev; } ;

/* Variables and functions */
 scalar_t__ BRCMS_ISLCNPHY (TYPE_1__*) ; 
 scalar_t__ BRCMS_ISNPHY (TYPE_1__*) ; 
 int /*<<< orphan*/  M_SYNTHPU_DLY ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYNTHPU_DLY_BPHY_US ; 
 int /*<<< orphan*/  SYNTHPU_DLY_LPPHY_US ; 
 int /*<<< orphan*/  SYNTHPU_DLY_NPHY_US ; 
 int /*<<< orphan*/  brcms_b_write_shm (struct brcms_hardware*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_b_upd_synthpu(struct brcms_hardware *wlc_hw)
{
	u16 v;
	struct brcms_c_info *wlc = wlc_hw->wlc;
	/* update SYNTHPU_DLY */

	if (BRCMS_ISLCNPHY(wlc->band))
		v = SYNTHPU_DLY_LPPHY_US;
	else if (BRCMS_ISNPHY(wlc->band) && (NREV_GE(wlc->band->phyrev, 3)))
		v = SYNTHPU_DLY_NPHY_US;
	else
		v = SYNTHPU_DLY_BPHY_US;

	brcms_b_write_shm(wlc_hw, M_SYNTHPU_DLY, v);
}