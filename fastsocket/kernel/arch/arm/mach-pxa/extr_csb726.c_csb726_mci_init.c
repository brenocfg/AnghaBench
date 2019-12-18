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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_2__ {int /*<<< orphan*/  detect_delay; } ;

/* Variables and functions */
 TYPE_1__ csb726_mci_data ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 

__attribute__((used)) static int csb726_mci_init(struct device *dev,
		irq_handler_t detect, void *data)
{
	csb726_mci_data.detect_delay = msecs_to_jiffies(500);
	return 0;
}