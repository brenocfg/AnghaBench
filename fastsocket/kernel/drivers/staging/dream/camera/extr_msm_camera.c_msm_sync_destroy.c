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
struct msm_sync {int /*<<< orphan*/  wake_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_lock_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msm_sync_destroy(struct msm_sync *sync)
{
	wake_lock_destroy(&sync->wake_lock);
	return 0;
}