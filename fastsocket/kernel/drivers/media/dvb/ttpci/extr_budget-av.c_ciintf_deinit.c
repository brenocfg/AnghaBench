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
struct saa7146_dev {int dummy; } ;
struct TYPE_2__ {struct saa7146_dev* dev; } ;
struct budget_av {int /*<<< orphan*/  ca; TYPE_1__ budget; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASK_27 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  SAA7146_GPIO_INPUT ; 
 int /*<<< orphan*/  dvb_ca_en50221_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ciintf_deinit(struct budget_av *budget_av)
{
	struct saa7146_dev *saa = budget_av->budget.dev;

	saa7146_setgpio(saa, 0, SAA7146_GPIO_INPUT);
	saa7146_setgpio(saa, 1, SAA7146_GPIO_INPUT);
	saa7146_setgpio(saa, 2, SAA7146_GPIO_INPUT);
	saa7146_setgpio(saa, 3, SAA7146_GPIO_INPUT);

	/* release the CA device */
	dvb_ca_en50221_release(&budget_av->ca);

	/* disable DEBI pins */
	saa7146_write(saa, MC1, MASK_27);
}