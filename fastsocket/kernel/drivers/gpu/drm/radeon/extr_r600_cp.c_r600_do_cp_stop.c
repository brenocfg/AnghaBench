#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ cp_running; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  R600_CP_ME_CNTL ; 
 int R600_CP_ME_HALT ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 

void r600_do_cp_stop(drm_radeon_private_t *dev_priv)
{
	uint32_t cp_me;

	DRM_DEBUG("\n");

	cp_me = 0xff | R600_CP_ME_HALT;

	RADEON_WRITE(R600_CP_ME_CNTL, cp_me);

	dev_priv->cp_running = 0;
}