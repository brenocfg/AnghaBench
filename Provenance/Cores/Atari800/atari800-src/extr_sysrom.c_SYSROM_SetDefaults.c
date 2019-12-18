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
struct TYPE_2__ {int /*<<< orphan*/  unset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SYSROM_SIZE ; 
 TYPE_1__* SYSROM_roms ; 
 scalar_t__ num_unset_roms ; 

void SYSROM_SetDefaults(void)
{
	int i;
	for (i = 0; i < SYSROM_SIZE; ++i)
		SYSROM_roms[i].unset = FALSE;
	num_unset_roms = 0;
}