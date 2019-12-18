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
 char* AEL2005_OPT_EDC_NAME ; 
 char* AEL2005_TWX_EDC_NAME ; 
 char* AEL2020_TWX_EDC_NAME ; 
#define  EDC_OPT_AEL2005 130 
#define  EDC_TWX_AEL2005 129 
#define  EDC_TWX_AEL2020 128 

__attribute__((used)) static inline const char *get_edc_fw_name(int edc_idx)
{
	const char *fw_name = NULL;

	switch (edc_idx) {
	case EDC_OPT_AEL2005:
		fw_name = AEL2005_OPT_EDC_NAME;
		break;
	case EDC_TWX_AEL2005:
		fw_name = AEL2005_TWX_EDC_NAME;
		break;
	case EDC_TWX_AEL2020:
		fw_name = AEL2020_TWX_EDC_NAME;
		break;
	}
	return fw_name;
}