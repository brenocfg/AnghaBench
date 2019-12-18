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
struct TYPE_2__ {int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  bootloader_read_flash_id () ; 
 TYPE_1__ g_rom_flashchip ; 

void bootloader_flash_update_id()
{
    g_rom_flashchip.device_id = bootloader_read_flash_id();
}