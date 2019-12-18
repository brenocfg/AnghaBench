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
struct pxa27x_ohci {scalar_t__ mmio_base; } ;

/* Variables and functions */
 scalar_t__ UHCHR ; 
 int UHCHR_FHR ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void pxa27x_reset_hc(struct pxa27x_ohci *ohci)
{
	uint32_t uhchr = __raw_readl(ohci->mmio_base + UHCHR);

	__raw_writel(uhchr | UHCHR_FHR, ohci->mmio_base + UHCHR);
	udelay(11);
	__raw_writel(uhchr & ~UHCHR_FHR, ohci->mmio_base + UHCHR);
}