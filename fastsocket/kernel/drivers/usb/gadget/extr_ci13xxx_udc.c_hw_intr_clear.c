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

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CAP_USBINTR ; 
 int /*<<< orphan*/  CAP_USBSTS ; 
 int EINVAL ; 
 int REG_BITS ; 
 int /*<<< orphan*/  hw_cwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_intr_clear(int n)
{
	if (n >= REG_BITS)
		return -EINVAL;

	hw_cwrite(CAP_USBINTR, BIT(n), 0);
	hw_cwrite(CAP_USBSTS,  BIT(n), BIT(n));
	return 0;
}