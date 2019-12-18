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
struct TYPE_2__ {int /*<<< orphan*/  toggle; } ;

/* Variables and functions */
 scalar_t__ ANOMALY_05000311 ; 
 scalar_t__ ANOMALY_05000323 ; 
 int /*<<< orphan*/  AWA_DUMMY_READ (int /*<<< orphan*/ ) ; 
 TYPE_1__** gpio_array ; 
 size_t gpio_bank (unsigned int) ; 
 int /*<<< orphan*/  gpio_bit (unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore_hw (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save_hw (unsigned long) ; 
 int /*<<< orphan*/  toggle ; 

void set_gpio_toggle(unsigned gpio)
{
	unsigned long flags;
	if (ANOMALY_05000311 || ANOMALY_05000323)
		local_irq_save_hw(flags);
	gpio_array[gpio_bank(gpio)]->toggle = gpio_bit(gpio);
	if (ANOMALY_05000311 || ANOMALY_05000323) {
		AWA_DUMMY_READ(toggle);
		local_irq_restore_hw(flags);
	}
}