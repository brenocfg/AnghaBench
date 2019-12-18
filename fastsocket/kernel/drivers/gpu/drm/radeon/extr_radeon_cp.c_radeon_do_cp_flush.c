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
typedef  int /*<<< orphan*/  drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  RADEON_CP_RB_WPTR ; 
 int RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void radeon_do_cp_flush(drm_radeon_private_t * dev_priv)
{
	DRM_DEBUG("\n");
#if 0
	u32 tmp;

	tmp = RADEON_READ(RADEON_CP_RB_WPTR) | (1 << 31);
	RADEON_WRITE(RADEON_CP_RB_WPTR, tmp);
#endif
}