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
typedef  int /*<<< orphan*/  u32 ;
struct cmac {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_XGM_RX_CFG ; 
 int /*<<< orphan*/  A_XGM_RX_HASH_HIGH ; 
 int /*<<< orphan*/  A_XGM_RX_HASH_LOW ; 
 int F_COPYALLFRAMES ; 
 int F_DISBCAST ; 
 int F_ENHASHMCAST ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  t3_mac_disable_exact_filters (struct cmac*) ; 
 int /*<<< orphan*/  t3_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void t3_gate_rx_traffic(struct cmac *mac, u32 *rx_cfg,
			       u32 *rx_hash_high, u32 *rx_hash_low)
{
	/* stop Rx unicast traffic */
	t3_mac_disable_exact_filters(mac);

	/* stop broadcast, multicast, promiscuous mode traffic */
	*rx_cfg = t3_read_reg(mac->adapter, A_XGM_RX_CFG);
	t3_set_reg_field(mac->adapter, A_XGM_RX_CFG,
			 F_ENHASHMCAST | F_DISBCAST | F_COPYALLFRAMES,
			 F_DISBCAST);

	*rx_hash_high = t3_read_reg(mac->adapter, A_XGM_RX_HASH_HIGH);
	t3_write_reg(mac->adapter, A_XGM_RX_HASH_HIGH, 0);

	*rx_hash_low = t3_read_reg(mac->adapter, A_XGM_RX_HASH_LOW);
	t3_write_reg(mac->adapter, A_XGM_RX_HASH_LOW, 0);

	/* Leave time to drain max RX fifo */
	msleep(1);
}