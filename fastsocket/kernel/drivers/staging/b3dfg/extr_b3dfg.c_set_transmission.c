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
struct b3dfg_dev {scalar_t__ transmission_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_transmission (struct b3dfg_dev*) ; 
 int enable_transmission (struct b3dfg_dev*) ; 

__attribute__((used)) static int set_transmission(struct b3dfg_dev *fgdev, int enabled)
{
	int res = 0;

	if (enabled && !fgdev->transmission_enabled)
		res = enable_transmission(fgdev);
	else if (!enabled && fgdev->transmission_enabled)
		disable_transmission(fgdev);

	return res;
}