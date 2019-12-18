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
struct radeon_device {int /*<<< orphan*/  audio_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  r600_audio_engine_enable (struct radeon_device*,int) ; 

void r600_audio_fini(struct radeon_device *rdev)
{
	if (!rdev->audio_enabled)
		return;

	r600_audio_engine_enable(rdev, false);
}