#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tx_packets; } ;
struct TYPE_5__ {TYPE_1__ linux_stats; } ;
typedef  TYPE_2__ wlandevice_t ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

void prism2sta_ev_tx(wlandevice_t *wlandev, u16 status)
{
	pr_debug("Tx Complete, status=0x%04x\n", status);
	/* update linux network stats */
	wlandev->linux_stats.tx_packets++;
	return;
}