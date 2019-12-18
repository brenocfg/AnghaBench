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
typedef  int /*<<< orphan*/  u8 ;
struct tda18218_priv {int dummy; } ;

/* Variables and functions */
 int tda18218_rd_regs (struct tda18218_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tda18218_rd_reg(struct tda18218_priv *priv, u8 reg, u8 *val)
{
	return tda18218_rd_regs(priv, reg, val, 1);
}