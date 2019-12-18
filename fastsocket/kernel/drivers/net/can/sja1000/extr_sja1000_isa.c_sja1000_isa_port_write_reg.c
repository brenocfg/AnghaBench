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
struct sja1000_priv {scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void sja1000_isa_port_write_reg(const struct sja1000_priv *priv,
				       int reg, u8 val)
{
	outb(val, (unsigned long)priv->reg_base + reg);
}