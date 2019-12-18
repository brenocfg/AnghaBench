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
struct rfkill {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  rfkill_pause_polling (struct rfkill*) ; 
 struct rfkill* to_rfkill (struct device*) ; 

__attribute__((used)) static int rfkill_suspend(struct device *dev, pm_message_t state)
{
	struct rfkill *rfkill = to_rfkill(dev);

	rfkill_pause_polling(rfkill);

	return 0;
}