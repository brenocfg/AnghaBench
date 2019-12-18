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
struct niu {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFDOWN ; 
 int /*<<< orphan*/  niu_disable_ipp (struct niu*) ; 
 int /*<<< orphan*/  niu_enable_interrupts (struct niu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_enable_rx_mac (struct niu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_reset_rx_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_reset_tx_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_stop_rx_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_stop_tx_channels (struct niu*) ; 
 int /*<<< orphan*/  niudbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_stop_hw(struct niu *np)
{
	niudbg(IFDOWN, "%s: Disable interrupts\n", np->dev->name);
	niu_enable_interrupts(np, 0);

	niudbg(IFDOWN, "%s: Disable RX MAC\n", np->dev->name);
	niu_enable_rx_mac(np, 0);

	niudbg(IFDOWN, "%s: Disable IPP\n", np->dev->name);
	niu_disable_ipp(np);

	niudbg(IFDOWN, "%s: Stop TX channels\n", np->dev->name);
	niu_stop_tx_channels(np);

	niudbg(IFDOWN, "%s: Stop RX channels\n", np->dev->name);
	niu_stop_rx_channels(np);

	niudbg(IFDOWN, "%s: Reset TX channels\n", np->dev->name);
	niu_reset_tx_channels(np);

	niudbg(IFDOWN, "%s: Reset RX channels\n", np->dev->name);
	niu_reset_rx_channels(np);
}