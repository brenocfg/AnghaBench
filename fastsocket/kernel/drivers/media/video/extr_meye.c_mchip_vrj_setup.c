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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MCHIP_VRJ_BUS_MODE ; 
 int /*<<< orphan*/  MCHIP_VRJ_COMP_DATA_FORMAT ; 
 int /*<<< orphan*/  MCHIP_VRJ_IRQ_FLAG ; 
 int /*<<< orphan*/  MCHIP_VRJ_LIMIT_COMPRESSED_HI ; 
 int /*<<< orphan*/  MCHIP_VRJ_LIMIT_COMPRESSED_LO ; 
 int /*<<< orphan*/  MCHIP_VRJ_MODE_SPECIFY ; 
 int /*<<< orphan*/  MCHIP_VRJ_NUM_COMPONENTS ; 
 int /*<<< orphan*/  MCHIP_VRJ_NUM_LINES ; 
 int /*<<< orphan*/  MCHIP_VRJ_NUM_PIXELS ; 
 int /*<<< orphan*/  MCHIP_VRJ_PDAT_USE ; 
 int /*<<< orphan*/  MCHIP_VRJ_RESTART_INTERVAL ; 
 int /*<<< orphan*/  MCHIP_VRJ_SIGNAL_ACTIVE_LEVEL ; 
 int /*<<< orphan*/  MCHIP_VRJ_SOF1 ; 
 int /*<<< orphan*/  MCHIP_VRJ_SOF2 ; 
 int /*<<< orphan*/  MCHIP_VRJ_SOF3 ; 
 int /*<<< orphan*/  MCHIP_VRJ_SOF4 ; 
 int /*<<< orphan*/  MCHIP_VRJ_SOS ; 
 int mchip_hsize () ; 
 int /*<<< orphan*/  mchip_load_tables () ; 
 int /*<<< orphan*/  mchip_set (int /*<<< orphan*/ ,int) ; 
 int mchip_vsize () ; 

__attribute__((used)) static void mchip_vrj_setup(u8 mode)
{
	mchip_set(MCHIP_VRJ_BUS_MODE, 5);
	mchip_set(MCHIP_VRJ_SIGNAL_ACTIVE_LEVEL, 0x1f);
	mchip_set(MCHIP_VRJ_PDAT_USE, 1);
	mchip_set(MCHIP_VRJ_IRQ_FLAG, 0xa0);
	mchip_set(MCHIP_VRJ_MODE_SPECIFY, mode);
	mchip_set(MCHIP_VRJ_NUM_LINES, mchip_vsize());
	mchip_set(MCHIP_VRJ_NUM_PIXELS, mchip_hsize());
	mchip_set(MCHIP_VRJ_NUM_COMPONENTS, 0x1b);
	mchip_set(MCHIP_VRJ_LIMIT_COMPRESSED_LO, 0xFFFF);
	mchip_set(MCHIP_VRJ_LIMIT_COMPRESSED_HI, 0xFFFF);
	mchip_set(MCHIP_VRJ_COMP_DATA_FORMAT, 0xC);
	mchip_set(MCHIP_VRJ_RESTART_INTERVAL, 0);
	mchip_set(MCHIP_VRJ_SOF1, 0x601);
	mchip_set(MCHIP_VRJ_SOF2, 0x1502);
	mchip_set(MCHIP_VRJ_SOF3, 0x1503);
	mchip_set(MCHIP_VRJ_SOF4, 0x1596);
	mchip_set(MCHIP_VRJ_SOS, 0x0ed0);

	mchip_load_tables();
}