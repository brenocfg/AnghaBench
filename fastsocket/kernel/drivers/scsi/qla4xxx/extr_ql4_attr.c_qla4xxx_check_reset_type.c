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
 int QL4_SCSI_ADAPTER_RESET ; 
 int QL4_SCSI_FIRMWARE_RESET ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int qla4xxx_check_reset_type(char *str)
{
	if (strncmp(str, "adapter", 10) == 0)
		return QL4_SCSI_ADAPTER_RESET;
	else if (strncmp(str, "firmware", 10) == 0)
		return QL4_SCSI_FIRMWARE_RESET;
	else
		return 0;
}