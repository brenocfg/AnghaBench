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
typedef  int sector_t ;

/* Variables and functions */
 int scsi_debug_sector_size ; 
 scalar_t__ scsi_debug_virtual_gb ; 
 int sdebug_store_sectors ; 

__attribute__((used)) static sector_t get_sdebug_capacity(void)
{
	if (scsi_debug_virtual_gb > 0)
		return (sector_t)scsi_debug_virtual_gb *
			(1073741824 / scsi_debug_sector_size);
	else
		return sdebug_store_sectors;
}