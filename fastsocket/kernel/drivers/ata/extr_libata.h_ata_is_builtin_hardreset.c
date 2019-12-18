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
typedef  scalar_t__ ata_reset_fn_t ;

/* Variables and functions */
 scalar_t__ sata_sff_hardreset ; 
 scalar_t__ sata_std_hardreset ; 

__attribute__((used)) static inline int ata_is_builtin_hardreset(ata_reset_fn_t reset)
{
	if (reset == sata_std_hardreset)
		return 1;
#ifdef CONFIG_ATA_SFF
	if (reset == sata_sff_hardreset)
		return 1;
#endif
	return 0;
}