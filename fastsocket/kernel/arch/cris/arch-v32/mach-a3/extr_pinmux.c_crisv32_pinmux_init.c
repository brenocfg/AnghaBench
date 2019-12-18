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

/* Variables and functions */
 int /*<<< orphan*/  PORT_A ; 
 int /*<<< orphan*/  PORT_B ; 
 int /*<<< orphan*/  PORT_C ; 
 int /*<<< orphan*/  REG_WR_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crisv32_pinmux_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinmux ; 
 int /*<<< orphan*/  pinmux_gpio ; 
 int /*<<< orphan*/  regi_pinmux ; 
 int /*<<< orphan*/  rw_hwprot ; 

int
crisv32_pinmux_init(void)
{
	static int initialized;

	if (!initialized) {
		initialized = 1;
		REG_WR_INT(pinmux, regi_pinmux, rw_hwprot, 0);
		crisv32_pinmux_alloc(PORT_A, 0, 31, pinmux_gpio);
		crisv32_pinmux_alloc(PORT_B, 0, 31, pinmux_gpio);
		crisv32_pinmux_alloc(PORT_C, 0, 15, pinmux_gpio);
	}

	return 0;
}