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
struct fb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_flip; int /*<<< orphan*/  f_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ ps3fb ; 
 int /*<<< orphan*/  ps3fb_sync (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_console_sem () ; 
 int /*<<< orphan*/  try_acquire_console_sem () ; 

__attribute__((used)) static int ps3fb_release(struct fb_info *info, int user)
{
	if (atomic_dec_and_test(&ps3fb.f_count)) {
		if (atomic_read(&ps3fb.ext_flip)) {
			atomic_set(&ps3fb.ext_flip, 0);
			if (!try_acquire_console_sem()) {
				ps3fb_sync(info, 0);	/* single buffer */
				release_console_sem();
			}
		}
	}
	return 0;
}