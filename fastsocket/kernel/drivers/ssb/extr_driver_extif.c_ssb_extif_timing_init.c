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
struct ssb_extif {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,unsigned long) ; 
 int SSB_EXTCFG_EN ; 
 int /*<<< orphan*/  SSB_EXTIF_PROG_CFG ; 
 int /*<<< orphan*/  SSB_EXTIF_PROG_WAITCNT ; 
 int SSB_PROG_WCNT_1_SHIFT ; 
 int SSB_PROG_WCNT_2_SHIFT ; 
 int SSB_PROG_WCNT_3_SHIFT ; 
 int /*<<< orphan*/  extif_write32 (struct ssb_extif*,int /*<<< orphan*/ ,int) ; 

void ssb_extif_timing_init(struct ssb_extif *extif, unsigned long ns)
{
	u32 tmp;

	/* Initialize extif so we can get to the LEDs and external UART */
	extif_write32(extif, SSB_EXTIF_PROG_CFG, SSB_EXTCFG_EN);

	/* Set timing for the flash */
	tmp  = DIV_ROUND_UP(10, ns) << SSB_PROG_WCNT_3_SHIFT;
	tmp |= DIV_ROUND_UP(40, ns) << SSB_PROG_WCNT_1_SHIFT;
	tmp |= DIV_ROUND_UP(120, ns);
	extif_write32(extif, SSB_EXTIF_PROG_WAITCNT, tmp);

	/* Set programmable interface timing for external uart */
	tmp  = DIV_ROUND_UP(10, ns) << SSB_PROG_WCNT_3_SHIFT;
	tmp |= DIV_ROUND_UP(20, ns) << SSB_PROG_WCNT_2_SHIFT;
	tmp |= DIV_ROUND_UP(100, ns) << SSB_PROG_WCNT_1_SHIFT;
	tmp |= DIV_ROUND_UP(120, ns);
	extif_write32(extif, SSB_EXTIF_PROG_WAITCNT, tmp);
}