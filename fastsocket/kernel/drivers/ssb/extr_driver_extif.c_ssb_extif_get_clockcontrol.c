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
typedef  int /*<<< orphan*/  u32 ;
struct ssb_extif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_EXTIF_CLOCK_N ; 
 int /*<<< orphan*/  SSB_EXTIF_CLOCK_SB ; 
 int /*<<< orphan*/  SSB_PLLTYPE_1 ; 
 int /*<<< orphan*/  extif_read32 (struct ssb_extif*,int /*<<< orphan*/ ) ; 

void ssb_extif_get_clockcontrol(struct ssb_extif *extif,
				u32 *pll_type, u32 *n, u32 *m)
{
	*pll_type = SSB_PLLTYPE_1;
	*n = extif_read32(extif, SSB_EXTIF_CLOCK_N);
	*m = extif_read32(extif, SSB_EXTIF_CLOCK_SB);
}