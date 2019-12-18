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
struct TYPE_2__ {int /*<<< orphan*/  fixups; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLANETCORE_KEY_MB_RAM ; 
 int /*<<< orphan*/  _dtb_start ; 
 scalar_t__ _end ; 
 int /*<<< orphan*/  fdt_init (int /*<<< orphan*/ ) ; 
 int mem_size ; 
 int /*<<< orphan*/  planetcore_get_decimal (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  planetcore_prepare_table (char*) ; 
 int /*<<< orphan*/  planetcore_set_stdout_path (char*) ; 
 int /*<<< orphan*/  platform_fixups ; 
 TYPE_1__ platform_ops ; 
 int /*<<< orphan*/  serial_console_init () ; 
 int /*<<< orphan*/  simple_alloc_init (scalar_t__,int,int,int) ; 
 char* table ; 

void platform_init(unsigned long r3, unsigned long r4, unsigned long r5,
		   unsigned long r6, unsigned long r7)
{
	table = (char *)r3;
	planetcore_prepare_table(table);

	if (!planetcore_get_decimal(table, PLANETCORE_KEY_MB_RAM, &mem_size))
		return;

	mem_size *= 1024 * 1024;
	simple_alloc_init(_end, mem_size - (unsigned long)_end, 32, 64);

	fdt_init(_dtb_start);

	planetcore_set_stdout_path(table);

	serial_console_init();
	platform_ops.fixups = platform_fixups;
}