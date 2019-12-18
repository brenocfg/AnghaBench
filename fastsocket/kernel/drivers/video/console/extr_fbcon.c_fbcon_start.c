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
 int FB_MAX ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 int /*<<< orphan*/  fbcon_takeover (int /*<<< orphan*/ ) ; 
 int info_idx ; 
 scalar_t__ num_registered_fb ; 
 int /*<<< orphan*/ ** registered_fb ; 
 int /*<<< orphan*/  release_console_sem () ; 

__attribute__((used)) static void fbcon_start(void)
{
	if (num_registered_fb) {
		int i;

		acquire_console_sem();

		for (i = 0; i < FB_MAX; i++) {
			if (registered_fb[i] != NULL) {
				info_idx = i;
				break;
			}
		}

		release_console_sem();
		fbcon_takeover(0);
	}
}