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
typedef  int u32 ;
struct TYPE_3__ {int usec_timeout; } ;
typedef  TYPE_1__ drm_mga_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  MGA_CRTC_INDEX ; 
 int MGA_ENDPRDMASTS ; 
 int MGA_ENGINE_IDLE_MASK ; 
 int MGA_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGA_STATUS ; 
 int /*<<< orphan*/  MGA_WRITE8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mga_do_wait_for_idle(drm_mga_private_t *dev_priv)
{
	u32 status = 0;
	int i;
	DRM_DEBUG("\n");

	for (i = 0; i < dev_priv->usec_timeout; i++) {
		status = MGA_READ(MGA_STATUS) & MGA_ENGINE_IDLE_MASK;
		if (status == MGA_ENDPRDMASTS) {
			MGA_WRITE8(MGA_CRTC_INDEX, 0);
			return 0;
		}
		DRM_UDELAY(1);
	}

#if MGA_DMA_DEBUG
	DRM_ERROR("failed!\n");
	DRM_INFO("   status=0x%08x\n", status);
#endif
	return -EBUSY;
}