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
typedef  int /*<<< orphan*/  drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  COMMIT_RING () ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  RADEON_PURGE_CACHE () ; 
 int /*<<< orphan*/  RADEON_PURGE_ZCACHE () ; 
 int /*<<< orphan*/  RADEON_WAIT_UNTIL_IDLE () ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int radeon_do_wait_for_idle (int /*<<< orphan*/ *) ; 

int radeon_do_cp_idle(drm_radeon_private_t * dev_priv)
{
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(6);

	RADEON_PURGE_CACHE();
	RADEON_PURGE_ZCACHE();
	RADEON_WAIT_UNTIL_IDLE();

	ADVANCE_RING();
	COMMIT_RING();

	return radeon_do_wait_for_idle(dev_priv);
}