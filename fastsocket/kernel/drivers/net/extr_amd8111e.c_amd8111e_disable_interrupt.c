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
struct amd8111e_priv {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ CMD0 ; 
 scalar_t__ INT0 ; 
 int /*<<< orphan*/  INTREN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void amd8111e_disable_interrupt(struct amd8111e_priv* lp)
{
	u32 intr0;

	/* Disable interrupt */
	writel(INTREN, lp->mmio + CMD0);

	/* Clear INT0 */
	intr0 = readl(lp->mmio + INT0);
	writel(intr0, lp->mmio + INT0);

	/* To avoid PCI posting bug */
	readl(lp->mmio + INT0);

}