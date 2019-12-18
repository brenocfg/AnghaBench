#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  cell_virtual_cntr ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 TYPE_1__ timer_virt_cntr ; 

__attribute__((used)) static void start_virt_cntrs(void)
{
	init_timer(&timer_virt_cntr);
	timer_virt_cntr.function = cell_virtual_cntr;
	timer_virt_cntr.data = 0UL;
	timer_virt_cntr.expires = jiffies + HZ / 10;
	add_timer(&timer_virt_cntr);
}