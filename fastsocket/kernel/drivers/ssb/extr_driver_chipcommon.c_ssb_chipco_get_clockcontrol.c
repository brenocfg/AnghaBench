#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ssb_chipcommon {int capabilities; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {int chip_id; } ;

/* Variables and functions */
 int SSB_CHIPCO_CAP_PLLT ; 
 int /*<<< orphan*/  SSB_CHIPCO_CLOCK_M2 ; 
 int /*<<< orphan*/  SSB_CHIPCO_CLOCK_MIPS ; 
 int /*<<< orphan*/  SSB_CHIPCO_CLOCK_N ; 
 int /*<<< orphan*/  SSB_CHIPCO_CLOCK_SB ; 
#define  SSB_PLLTYPE_3 129 
#define  SSB_PLLTYPE_6 128 
 int chipco_read32 (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 

void ssb_chipco_get_clockcontrol(struct ssb_chipcommon *cc,
				 u32 *plltype, u32 *n, u32 *m)
{
	*n = chipco_read32(cc, SSB_CHIPCO_CLOCK_N);
	*plltype = (cc->capabilities & SSB_CHIPCO_CAP_PLLT);
	switch (*plltype) {
	case SSB_PLLTYPE_6: /* 100/200 or 120/240 only */
		*m = chipco_read32(cc, SSB_CHIPCO_CLOCK_MIPS);
		break;
	case SSB_PLLTYPE_3: /* 25Mhz, 2 dividers */
		if (cc->dev->bus->chip_id != 0x5365) {
			*m = chipco_read32(cc, SSB_CHIPCO_CLOCK_M2);
			break;
		}
		/* Fallthough */
	default:
		*m = chipco_read32(cc, SSB_CHIPCO_CLOCK_SB);
	}
}