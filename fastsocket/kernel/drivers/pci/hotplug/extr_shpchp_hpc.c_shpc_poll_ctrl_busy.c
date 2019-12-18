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
struct controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_ctrl_busy (struct controller*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static inline int shpc_poll_ctrl_busy(struct controller *ctrl)
{
	int i;

	if (!is_ctrl_busy(ctrl))
		return 1;

	/* Check every 0.1 sec for a total of 1 sec */
	for (i = 0; i < 10; i++) {
		msleep(100);
		if (!is_ctrl_busy(ctrl))
			return 1;
	}

	return 0;
}