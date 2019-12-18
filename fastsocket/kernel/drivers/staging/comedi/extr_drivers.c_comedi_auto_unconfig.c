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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int COMEDI_NUM_BOARD_MINORS ; 
 int /*<<< orphan*/  comedi_free_board_minor (unsigned int) ; 
 scalar_t__ dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 

void comedi_auto_unconfig(struct device *hardware_device)
{
	unsigned *minor = (unsigned *)dev_get_drvdata(hardware_device);
	if (minor == NULL)
		return;

	BUG_ON(*minor >= COMEDI_NUM_BOARD_MINORS);

	comedi_free_board_minor(*minor);
	dev_set_drvdata(hardware_device, NULL);
	kfree(minor);
}