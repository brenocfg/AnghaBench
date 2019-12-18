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
struct rfkill {int state; int /*<<< orphan*/  persistent; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int RFKILL_BLOCK_SW ; 
 int /*<<< orphan*/  rfkill_resume_polling (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_set_block (struct rfkill*,int) ; 
 struct rfkill* to_rfkill (struct device*) ; 

__attribute__((used)) static int rfkill_resume(struct device *dev)
{
	struct rfkill *rfkill = to_rfkill(dev);
	bool cur;

	if (!rfkill->persistent) {
		cur = !!(rfkill->state & RFKILL_BLOCK_SW);
		rfkill_set_block(rfkill, cur);
	}

	rfkill_resume_polling(rfkill);

	return 0;
}