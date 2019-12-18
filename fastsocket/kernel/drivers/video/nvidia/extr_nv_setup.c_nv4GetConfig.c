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
struct nvidia_par {int RamAmountKBytes; int CrystalFreqKHz; int MinVClockFreqKHz; int MaxVClockFreqKHz; int /*<<< orphan*/ * PRAMIN; int /*<<< orphan*/ * CURSOR; int /*<<< orphan*/  PEXTDEV; int /*<<< orphan*/  PFB; } ;

/* Variables and functions */
 int NV_RD32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nv4GetConfig(struct nvidia_par *par)
{
	if (NV_RD32(par->PFB, 0x0000) & 0x00000100) {
		par->RamAmountKBytes =
		    ((NV_RD32(par->PFB, 0x0000) >> 12) & 0x0F) * 1024 * 2 +
		    1024 * 2;
	} else {
		switch (NV_RD32(par->PFB, 0x0000) & 0x00000003) {
		case 0:
			par->RamAmountKBytes = 1024 * 32;
			break;
		case 1:
			par->RamAmountKBytes = 1024 * 4;
			break;
		case 2:
			par->RamAmountKBytes = 1024 * 8;
			break;
		case 3:
		default:
			par->RamAmountKBytes = 1024 * 16;
			break;
		}
	}
	par->CrystalFreqKHz = (NV_RD32(par->PEXTDEV, 0x0000) & 0x00000040) ?
	    14318 : 13500;
	par->CURSOR = &par->PRAMIN[0x1E00];
	par->MinVClockFreqKHz = 12000;
	par->MaxVClockFreqKHz = 350000;
}