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
struct rx8025_data {int /*<<< orphan*/  work; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 struct rx8025_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rx8025_irq(int irq, void *dev_id)
{
	struct i2c_client *client = dev_id;
	struct rx8025_data *rx8025 = i2c_get_clientdata(client);

	disable_irq_nosync(irq);
	schedule_work(&rx8025->work);
	return IRQ_HANDLED;
}