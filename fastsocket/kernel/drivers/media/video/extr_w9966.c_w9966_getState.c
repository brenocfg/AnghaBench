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
struct w9966_dev {int dev_state; } ;

/* Variables and functions */

__attribute__((used)) static inline int w9966_getState(struct w9966_dev* cam, int mask, int val)
{
	return ((cam->dev_state & mask) == val);
}