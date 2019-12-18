#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* cleanup ) () ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__**) ; 
 TYPE_1__** config_rom_entries ; 
 int /*<<< orphan*/  stub1 () ; 

void hpsb_cleanup_config_roms(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(config_rom_entries); i++)
		config_rom_entries[i]->cleanup();
}