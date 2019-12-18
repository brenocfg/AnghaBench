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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_3__ {unsigned long data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SAMPLE_RANDOM ; 
 int /*<<< orphan*/  LUBBOCK_SD_IRQ ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  lubbock_detect_int ; 
 int /*<<< orphan*/  mmc_detect_int ; 
 TYPE_1__ mmc_timer ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int lubbock_mci_init(struct device *dev,
		irq_handler_t detect_int,
		void *data)
{
	/* detect card insert/eject */
	mmc_detect_int = detect_int;
	init_timer(&mmc_timer);
	mmc_timer.data = (unsigned long) data;
	return request_irq(LUBBOCK_SD_IRQ, lubbock_detect_int,
			IRQF_SAMPLE_RANDOM, "lubbock-sd-detect", data);
}