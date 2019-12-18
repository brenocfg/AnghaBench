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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_OUTPUT_HIGH ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_OUTPUT_LOW ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_84833_get_reset_gpios (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_mult_gpio (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bnx2x_84833_common_init_phy(struct bnx2x *bp,
						u32 shmem_base_path[],
						u32 shmem2_base_path[],
						u8 phy_index,
						u32 chip_id)
{
	u8 reset_gpios;
	reset_gpios = bnx2x_84833_get_reset_gpios(bp, shmem_base_path, chip_id);
	bnx2x_set_mult_gpio(bp, reset_gpios, MISC_REGISTERS_GPIO_OUTPUT_LOW);
	udelay(10);
	bnx2x_set_mult_gpio(bp, reset_gpios, MISC_REGISTERS_GPIO_OUTPUT_HIGH);
	DP(NETIF_MSG_LINK, "84833 reset pulse on pin values 0x%x\n",
		reset_gpios);
	return 0;
}