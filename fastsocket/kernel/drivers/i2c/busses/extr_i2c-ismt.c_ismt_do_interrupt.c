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
typedef  int u32 ;
struct ismt_priv {scalar_t__ smba; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ ISMT_MSTR_MSTS ; 
 int ISMT_MSTS_MEIS ; 
 int ISMT_MSTS_MIS ; 
 int /*<<< orphan*/  ismt_handle_isr (struct ismt_priv*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t ismt_do_interrupt(int vec, void *data)
{
	u32 val;
	struct ismt_priv *priv = data;

	/*
	 * check to see it's our interrupt, return IRQ_NONE if not ours
	 * since we are sharing interrupt
	 */
	val = readl(priv->smba + ISMT_MSTR_MSTS);

	if (!(val & (ISMT_MSTS_MIS | ISMT_MSTS_MEIS)))
		return IRQ_NONE;
	else
		writel(val | ISMT_MSTS_MIS | ISMT_MSTS_MEIS,
		       priv->smba + ISMT_MSTR_MSTS);

	return ismt_handle_isr(priv);
}