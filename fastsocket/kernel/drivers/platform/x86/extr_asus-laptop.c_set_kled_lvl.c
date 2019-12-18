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
 int EINVAL ; 
 int /*<<< orphan*/  kled_set_handle ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_kled_lvl(int kblv)
{
	if (kblv > 0)
		kblv = (1 << 7) | (kblv & 0x7F);
	else
		kblv = 0;

	if (write_acpi_int(kled_set_handle, NULL, kblv, NULL)) {
		pr_warning("Keyboard LED display write failed\n");
		return -EINVAL;
	}
	return 0;
}