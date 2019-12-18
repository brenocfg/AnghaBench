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
struct TYPE_2__ {int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  rx_timer; scalar_t__ ethtxq_rover; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 scalar_t__ RX_QCHECK_PERIOD ; 
 scalar_t__ TX_QCHECK_PERIOD ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

void t4_sge_start(struct adapter *adap)
{
	adap->sge.ethtxq_rover = 0;
	mod_timer(&adap->sge.rx_timer, jiffies + RX_QCHECK_PERIOD);
	mod_timer(&adap->sge.tx_timer, jiffies + TX_QCHECK_PERIOD);
}