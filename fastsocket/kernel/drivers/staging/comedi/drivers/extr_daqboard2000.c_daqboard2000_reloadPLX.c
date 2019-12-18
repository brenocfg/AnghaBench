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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ plx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAQBOARD2000_SECRReloadHi ; 
 int /*<<< orphan*/  DAQBOARD2000_SECRReloadLo ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void daqboard2000_reloadPLX(struct comedi_device *dev)
{
	printk("daqboard2000_reloadPLX\n");
	writel(DAQBOARD2000_SECRReloadLo, devpriv->plx + 0x6c);
	udelay(10000);
	writel(DAQBOARD2000_SECRReloadHi, devpriv->plx + 0x6c);
	udelay(10000);
	writel(DAQBOARD2000_SECRReloadLo, devpriv->plx + 0x6c);
	udelay(10000);
}