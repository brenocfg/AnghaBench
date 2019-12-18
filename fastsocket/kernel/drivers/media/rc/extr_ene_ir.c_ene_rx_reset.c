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
struct ene_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_CIRCFG ; 
 int /*<<< orphan*/  ENE_CIRCFG_RX_EN ; 
 int /*<<< orphan*/  ene_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_set_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ene_rx_reset(struct ene_device *dev)
{
	ene_clear_reg_mask(dev, ENE_CIRCFG, ENE_CIRCFG_RX_EN);
	ene_set_reg_mask(dev, ENE_CIRCFG, ENE_CIRCFG_RX_EN);
}