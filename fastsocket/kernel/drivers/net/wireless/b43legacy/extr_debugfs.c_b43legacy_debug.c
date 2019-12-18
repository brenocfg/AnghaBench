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
struct b43legacy_wldev {TYPE_1__* dfsentry; } ;
typedef  enum b43legacy_dyndbg { ____Placeholder_b43legacy_dyndbg } b43legacy_dyndbg ;
struct TYPE_2__ {scalar_t__* dyn_debug; } ;

/* Variables and functions */

int b43legacy_debug(struct b43legacy_wldev *dev, enum b43legacy_dyndbg feature)
{
	return !!(dev->dfsentry && dev->dfsentry->dyn_debug[feature]);
}