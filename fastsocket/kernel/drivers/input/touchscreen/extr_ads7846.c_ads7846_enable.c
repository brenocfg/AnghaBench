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
struct ads7846 {TYPE_1__* spi; scalar_t__ irq_disabled; scalar_t__ disabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ads7846_enable(struct ads7846 *ts)
{
	if (!ts->disabled)
		return;

	ts->disabled = 0;
	ts->irq_disabled = 0;
	enable_irq(ts->spi->irq);
}