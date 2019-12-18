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
struct pasemi_mac_txring {int /*<<< orphan*/  clean_timer; struct pasemi_mac* mac; } ;
struct pasemi_mac {int dummy; } ;

/* Variables and functions */
 scalar_t__ TX_CLEAN_INTERVAL ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pasemi_mac_clean_tx (struct pasemi_mac_txring*) ; 
 int /*<<< orphan*/  pasemi_mac_restart_tx_intr (struct pasemi_mac*) ; 

__attribute__((used)) static void pasemi_mac_tx_timer(unsigned long data)
{
	struct pasemi_mac_txring *txring = (struct pasemi_mac_txring *)data;
	struct pasemi_mac *mac = txring->mac;

	pasemi_mac_clean_tx(txring);

	mod_timer(&txring->clean_timer, jiffies + TX_CLEAN_INTERVAL);

	pasemi_mac_restart_tx_intr(mac);
}