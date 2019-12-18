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

/* Variables and functions */
#define  NAND_MFR_AMD 131 
#define  NAND_MFR_NATSEMI 130 
#define  NAND_MFR_SAMSUNG 129 
#define  NAND_MFR_TOSHIBA 128 

__attribute__((used)) static inline char *nand_flash_manufacturer(int manuf_id) {
	switch(manuf_id) {
	case NAND_MFR_AMD:
		return "AMD";
	case NAND_MFR_NATSEMI:
		return "NATSEMI";
	case NAND_MFR_TOSHIBA:
		return "Toshiba";
	case NAND_MFR_SAMSUNG:
		return "Samsung";
	default:
		return "unknown";
	}
}