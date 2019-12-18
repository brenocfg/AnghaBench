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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pmac_backlight_set_legacy_brightness (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_backlight_disabled ; 
 int /*<<< orphan*/  pmac_backlight_set_legacy_queued ; 

__attribute__((used)) static void pmac_backlight_set_legacy_worker(struct work_struct *work)
{
	if (atomic_read(&kernel_backlight_disabled))
		return;

	__pmac_backlight_set_legacy_brightness(pmac_backlight_set_legacy_queued);
}