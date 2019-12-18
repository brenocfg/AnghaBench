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
struct mwl8k_priv {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWL8K_H2A_INT_RESET ; 
 scalar_t__ MWL8K_HIU_H2A_INTERRUPT_EVENTS ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void mwl8k_hw_reset(struct mwl8k_priv *priv)
{
	iowrite32(MWL8K_H2A_INT_RESET,
		priv->regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);
	iowrite32(MWL8K_H2A_INT_RESET,
		priv->regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);
	msleep(20);
}