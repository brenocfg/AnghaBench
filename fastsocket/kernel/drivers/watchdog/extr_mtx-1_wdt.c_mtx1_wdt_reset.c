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
struct TYPE_2__ {int /*<<< orphan*/  default_ticks; } ;

/* Variables and functions */
 TYPE_1__ mtx1_wdt_device ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static void mtx1_wdt_reset(void)
{
	ticks = mtx1_wdt_device.default_ticks;
}