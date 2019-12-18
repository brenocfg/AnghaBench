#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pcf50633_input {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  pcf; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_POWER ; 
 int PCF50633_IRQ_ONKEYF ; 
 int PCF50633_IRQ_ONKEYR ; 
 int PCF50633_OOCSTAT_ONKEY ; 
 int /*<<< orphan*/  PCF50633_REG_OOCSTAT ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int pcf50633_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pcf50633_input_irq(int irq, void *data)
{
	struct pcf50633_input *input;
	int onkey_released;

	input = data;

	/* We report only one event depending on the key press status */
	onkey_released = pcf50633_reg_read(input->pcf, PCF50633_REG_OOCSTAT)
						& PCF50633_OOCSTAT_ONKEY;

	if (irq == PCF50633_IRQ_ONKEYF && !onkey_released)
		input_report_key(input->input_dev, KEY_POWER, 1);
	else if (irq == PCF50633_IRQ_ONKEYR && onkey_released)
		input_report_key(input->input_dev, KEY_POWER, 0);

	input_sync(input->input_dev);
}