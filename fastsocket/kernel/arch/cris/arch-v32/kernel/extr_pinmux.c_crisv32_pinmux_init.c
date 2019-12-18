#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pa7; int /*<<< orphan*/  pa6; int /*<<< orphan*/  pa5; int /*<<< orphan*/  pa4; int /*<<< orphan*/  pa3; int /*<<< orphan*/  pa2; int /*<<< orphan*/  pa1; int /*<<< orphan*/  pa0; } ;
typedef  TYPE_1__ reg_pinmux_rw_pa ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_B ; 
 int /*<<< orphan*/  PORT_C ; 
 int /*<<< orphan*/  PORT_D ; 
 int /*<<< orphan*/  PORT_E ; 
 scalar_t__ PORT_PINS ; 
 TYPE_1__ REG_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  crisv32_pinmux_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinmux ; 
 int /*<<< orphan*/  pinmux_gpio ; 
 int /*<<< orphan*/  regi_pinmux ; 
 int /*<<< orphan*/  regk_pinmux_yes ; 
 int /*<<< orphan*/  rw_pa ; 

int
crisv32_pinmux_init(void)
{
	static int initialized = 0;

	if (!initialized) {
		reg_pinmux_rw_pa pa = REG_RD(pinmux, regi_pinmux, rw_pa);
		initialized = 1;
		pa.pa0 = pa.pa1 = pa.pa2 = pa.pa3 =
		pa.pa4 = pa.pa5 = pa.pa6 = pa.pa7 = regk_pinmux_yes;
		REG_WR(pinmux, regi_pinmux, rw_pa, pa);
		crisv32_pinmux_alloc(PORT_B, 0, PORT_PINS - 1, pinmux_gpio);
		crisv32_pinmux_alloc(PORT_C, 0, PORT_PINS - 1, pinmux_gpio);
		crisv32_pinmux_alloc(PORT_D, 0, PORT_PINS - 1, pinmux_gpio);
		crisv32_pinmux_alloc(PORT_E, 0, PORT_PINS - 1, pinmux_gpio);
	}

	return 0;
}