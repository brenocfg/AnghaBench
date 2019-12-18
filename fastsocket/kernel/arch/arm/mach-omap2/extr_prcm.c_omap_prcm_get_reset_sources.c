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
 int /*<<< orphan*/  RM_RSTST ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 int prm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 omap_prcm_get_reset_sources(void)
{
	/* XXX This presumably needs modification for 34XX */
	return prm_read_mod_reg(WKUP_MOD, RM_RSTST) & 0x7f;
}