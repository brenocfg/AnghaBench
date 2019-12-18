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
struct acpi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cur_irq; int /*<<< orphan*/  cur_ioport; } ;

/* Variables and functions */
 int /*<<< orphan*/  sony_pic_enable (struct acpi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ spic_dev ; 

__attribute__((used)) static int sony_pic_resume(struct acpi_device *device)
{
	sony_pic_enable(device, spic_dev.cur_ioport, spic_dev.cur_irq);
	return 0;
}