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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio12_config_gpio ; 
 int /*<<< orphan*/  pxa2xx_mfp_config (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clk_gpio12_disable(struct clk *clk)
{
	pxa2xx_mfp_config(gpio12_config_gpio, 1);
}