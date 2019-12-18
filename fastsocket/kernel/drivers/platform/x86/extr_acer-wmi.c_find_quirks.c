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
 int /*<<< orphan*/  acer_quirks ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int force_series ; 
 int /*<<< orphan*/  quirk_acer_travelmate_2490 ; 
 int /*<<< orphan*/  quirk_unknown ; 
 int /*<<< orphan*/ * quirks ; 
 int /*<<< orphan*/  set_quirks () ; 

__attribute__((used)) static void find_quirks(void)
{
	if (!force_series) {
		dmi_check_system(acer_quirks);
	} else if (force_series == 2490) {
		quirks = &quirk_acer_travelmate_2490;
	}

	if (quirks == NULL)
		quirks = &quirk_unknown;

	set_quirks();
}