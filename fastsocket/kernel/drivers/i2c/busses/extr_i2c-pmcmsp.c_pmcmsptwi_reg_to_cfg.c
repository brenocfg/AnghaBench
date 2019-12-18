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
struct pmcmsptwi_cfg {int arbf; int nak; int add10; int mst_code; int arb; int highspeed; } ;

/* Variables and functions */

__attribute__((used)) static inline void pmcmsptwi_reg_to_cfg(u32 reg, struct pmcmsptwi_cfg *cfg)
{
	cfg->arbf = (reg >> 12) & 0xf;
	cfg->nak = (reg >> 8) & 0xf;
	cfg->add10 = (reg >> 7) & 0x1;
	cfg->mst_code = (reg >> 4) & 0x7;
	cfg->arb = (reg >> 1) & 0x1;
	cfg->highspeed = reg & 0x1;
}