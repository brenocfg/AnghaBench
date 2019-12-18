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
struct TYPE_2__ {int /*<<< orphan*/  gc; } ;
struct mcu {int /*<<< orphan*/  np; TYPE_1__ of_gc; } ;

/* Variables and functions */
 int gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcu_gpiochip_remove(struct mcu *mcu)
{
	int ret;

	ret = gpiochip_remove(&mcu->of_gc.gc);
	if (ret)
		return ret;
	of_node_put(mcu->np);

	return 0;
}