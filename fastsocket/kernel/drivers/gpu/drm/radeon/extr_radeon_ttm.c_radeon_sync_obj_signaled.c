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
struct radeon_fence {int dummy; } ;

/* Variables and functions */
 int radeon_fence_signaled (struct radeon_fence*) ; 

__attribute__((used)) static bool radeon_sync_obj_signaled(void *sync_obj)
{
	return radeon_fence_signaled((struct radeon_fence *)sync_obj);
}