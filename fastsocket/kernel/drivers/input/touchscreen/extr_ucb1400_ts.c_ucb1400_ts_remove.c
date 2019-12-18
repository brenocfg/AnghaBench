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
struct ucb1400_ts {int /*<<< orphan*/  ts_idev; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {struct ucb1400_ts* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ucb1400_ts*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucb1400_ts_remove(struct platform_device *dev)
{
	struct ucb1400_ts *ucb = dev->dev.platform_data;

	free_irq(ucb->irq, ucb);
	input_unregister_device(ucb->ts_idev);
	return 0;
}