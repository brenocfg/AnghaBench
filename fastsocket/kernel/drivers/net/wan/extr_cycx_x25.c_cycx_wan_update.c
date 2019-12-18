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
struct wan_device {scalar_t__ state; int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 scalar_t__ WAN_UNCONFIGURED ; 
 int /*<<< orphan*/  cycx_x25_get_stats (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cycx_wan_update(struct wan_device *wandev)
{
	/* sanity checks */
	if (!wandev || !wandev->private)
		return -EFAULT;

	if (wandev->state == WAN_UNCONFIGURED)
		return -ENODEV;

	cycx_x25_get_stats(wandev->private);

	return 0;
}