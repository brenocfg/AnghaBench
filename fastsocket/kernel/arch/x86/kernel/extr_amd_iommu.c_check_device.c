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
struct device {int /*<<< orphan*/  dma_mask; } ;

/* Variables and functions */

__attribute__((used)) static bool check_device(struct device *dev)
{
	if (!dev || !dev->dma_mask)
		return false;

	return true;
}