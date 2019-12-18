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
struct TYPE_2__ {int offset; int /*<<< orphan*/  srambuf; int /*<<< orphan*/  sync; scalar_t__ locked; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sram_read (int /*<<< orphan*/ ) ; 
 TYPE_1__ sramcntrl ; 

void __sram_init()
{
	sramcntrl.enabled = 0;
	sramcntrl.locked = 0;
	sramcntrl.sync = __sram_read(sramcntrl.srambuf);

	sramcntrl.offset = 64;
}