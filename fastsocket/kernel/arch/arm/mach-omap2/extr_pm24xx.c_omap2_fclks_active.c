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

/* Variables and functions */
 int /*<<< orphan*/  CM_FCLKEN1 ; 
 int /*<<< orphan*/  CORE_MOD ; 
 int /*<<< orphan*/  OMAP24XX_CM_FCLKEN2 ; 
 int OMAP24XX_EN_UART1 ; 
 int OMAP24XX_EN_UART2 ; 
 int OMAP24XX_EN_UART3 ; 
 int cm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2_fclks_active(void)
{
	u32 f1, f2;

	f1 = cm_read_mod_reg(CORE_MOD, CM_FCLKEN1);
	f2 = cm_read_mod_reg(CORE_MOD, OMAP24XX_CM_FCLKEN2);

	/* Ignore UART clocks.  These are handled by UART core (serial.c) */
	f1 &= ~(OMAP24XX_EN_UART1 | OMAP24XX_EN_UART2);
	f2 &= ~OMAP24XX_EN_UART3;

	if (f1 | f2)
		return 1;
	return 0;
}