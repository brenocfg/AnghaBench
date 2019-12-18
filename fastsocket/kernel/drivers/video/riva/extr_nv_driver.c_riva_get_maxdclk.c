#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int Architecture; int /*<<< orphan*/  PFB; int /*<<< orphan*/  PMC; } ;
struct riva_par {TYPE_1__ riva; } ;
typedef  TYPE_1__ RIVA_HW_INST ;

/* Variables and functions */
#define  NV_ARCH_03 132 
#define  NV_ARCH_04 131 
#define  NV_ARCH_10 130 
#define  NV_ARCH_20 129 
#define  NV_ARCH_30 128 
 int NV_RD32 (int /*<<< orphan*/ ,int) ; 

unsigned long riva_get_maxdclk(struct riva_par *par)
{
	RIVA_HW_INST *chip = &par->riva;
	unsigned long dclk = 0;

	switch (chip->Architecture) {
	case NV_ARCH_03:
		if (NV_RD32(chip->PFB, 0x00000000) & 0x00000020) {
			if (((NV_RD32(chip->PMC, 0x00000000) & 0xF0) == 0x20)
			    && ((NV_RD32(chip->PMC,0x00000000)&0x0F) >= 0x02)) {
				/*
				 * SDRAM 128 ZX.
				 */
				dclk = 800000;
			} else {
				dclk = 1000000;
			}            
		} else {
			/*
			 * SGRAM 128.
			 */
			dclk = 1000000;
		} 
		break;
	case NV_ARCH_04:
	case NV_ARCH_10:
	case NV_ARCH_20:
	case NV_ARCH_30:
		switch ((NV_RD32(chip->PFB, 0x00000000) >> 3) & 0x00000003) {
		case 3:
			dclk = 800000;
			break;
		default:
			dclk = 1000000;
			break;
		}
		break;
	}
	return dclk;
}