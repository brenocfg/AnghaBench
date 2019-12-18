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
struct atmel_nand_host {TYPE_1__* board; } ;
struct TYPE_2__ {scalar_t__ enable_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (scalar_t__,int) ; 

__attribute__((used)) static void atmel_nand_disable(struct atmel_nand_host *host)
{
	if (host->board->enable_pin)
		gpio_set_value(host->board->enable_pin, 1);
}