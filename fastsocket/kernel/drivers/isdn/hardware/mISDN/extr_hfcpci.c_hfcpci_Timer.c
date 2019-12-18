#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct TYPE_4__ {TYPE_1__ timer; } ;
struct hfc_pci {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 

__attribute__((used)) static void
hfcpci_Timer(struct hfc_pci *hc)
{
	hc->hw.timer.expires = jiffies + 75;
	/* WD RESET */
/*
 *	WriteReg(hc, HFCD_DATA, HFCD_CTMT, hc->hw.ctmt | 0x80);
 *	add_timer(&hc->hw.timer);
 */
}