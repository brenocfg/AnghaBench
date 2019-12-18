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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_USBSTS ; 
 int /*<<< orphan*/  hw_cwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hw_read_intr_enable () ; 
 int hw_read_intr_status () ; 

__attribute__((used)) static u32 hw_test_and_clear_intr_active(void)
{
	u32 reg = hw_read_intr_status() & hw_read_intr_enable();

	hw_cwrite(CAP_USBSTS, ~0, reg);
	return reg;
}