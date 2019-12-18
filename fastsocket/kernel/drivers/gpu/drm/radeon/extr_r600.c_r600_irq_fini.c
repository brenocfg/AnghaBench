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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r600_ih_ring_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_irq_suspend (struct radeon_device*) ; 

void r600_irq_fini(struct radeon_device *rdev)
{
	r600_irq_suspend(rdev);
	r600_ih_ring_fini(rdev);
}