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
typedef  int uint32_t ;
struct pxaohci_platform_data {int /*<<< orphan*/  (* exit ) (struct device*) ;} ;
struct pxa27x_ohci {int /*<<< orphan*/  clk; scalar_t__ mmio_base; } ;
struct device {struct pxaohci_platform_data* platform_data; } ;

/* Variables and functions */
 scalar_t__ UHCCOMS ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa27x_reset_hc (struct pxa27x_ohci*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pxa27x_stop_hc(struct pxa27x_ohci *ohci, struct device *dev)
{
	struct pxaohci_platform_data *inf;
	uint32_t uhccoms;

	inf = dev->platform_data;

	if (inf->exit)
		inf->exit(dev);

	pxa27x_reset_hc(ohci);

	/* Host Controller Reset */
	uhccoms = __raw_readl(ohci->mmio_base + UHCCOMS) | 0x01;
	__raw_writel(uhccoms, ohci->mmio_base + UHCCOMS);
	udelay(10);

	clk_disable(ohci->clk);
}