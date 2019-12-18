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
struct ppc4xx_ecc_status {int ecces; } ;

/* Variables and functions */
 int SDRAM_ECCES_BK0ER ; 
 int SDRAM_ECCES_BK1ER ; 

__attribute__((used)) static bool
ppc4xx_edac_check_bank_error(const struct ppc4xx_ecc_status *status,
			     unsigned int bank)
{
	switch (bank) {
	case 0:
		return status->ecces & SDRAM_ECCES_BK0ER;
	case 1:
		return status->ecces & SDRAM_ECCES_BK1ER;
	default:
		return false;
	}
}