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
struct sym_nvram {int type; } ;

/* Variables and functions */
#define  SYM_PARISC_PDC 130 
#define  SYM_SYMBIOS_NVRAM 129 
#define  SYM_TEKRAM_NVRAM 128 

char *sym_nvram_type(struct sym_nvram *nvp)
{
	switch (nvp->type) {
	case SYM_SYMBIOS_NVRAM:
		return "Symbios NVRAM";
	case SYM_TEKRAM_NVRAM:
		return "Tekram NVRAM";
	case SYM_PARISC_PDC:
		return "PA-RISC Firmware";
	default:
		return "No NVRAM";
	}
}