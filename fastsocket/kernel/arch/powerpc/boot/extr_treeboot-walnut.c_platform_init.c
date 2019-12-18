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
struct TYPE_2__ {int /*<<< orphan*/  exit; int /*<<< orphan*/  fixups; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dtb_start ; 
 scalar_t__ _end ; 
 int /*<<< orphan*/  fdt_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibm40x_dbcr_reset ; 
 TYPE_1__ platform_ops ; 
 int /*<<< orphan*/  serial_console_init () ; 
 int /*<<< orphan*/  simple_alloc_init (scalar_t__,unsigned long,int,int) ; 
 int /*<<< orphan*/  walnut_fixups ; 

void platform_init(void)
{
	unsigned long end_of_ram = 0x2000000;
	unsigned long avail_ram = end_of_ram - (unsigned long) _end;

	simple_alloc_init(_end, avail_ram, 32, 32);
	platform_ops.fixups = walnut_fixups;
	platform_ops.exit = ibm40x_dbcr_reset;
	fdt_init(_dtb_start);
	serial_console_init();
}