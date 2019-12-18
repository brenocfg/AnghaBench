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
struct comedi_device {int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  C6X_encResetAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C6X_pwmInit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void board_init(struct comedi_device *dev)
{

	/* printk("Inside board_init\n"); */

	C6X_pwmInit(dev->iobase);
	C6X_encResetAll(dev->iobase);

}