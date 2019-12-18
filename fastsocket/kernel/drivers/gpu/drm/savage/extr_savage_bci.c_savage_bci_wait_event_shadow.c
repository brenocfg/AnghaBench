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
typedef  int uint16_t ;
struct TYPE_3__ {int* status_ptr; } ;
typedef  TYPE_1__ drm_savage_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int,int) ; 
 int /*<<< orphan*/  DRM_MEMORYBARRIER () ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 int EBUSY ; 
 int SAVAGE_EVENT_USEC_TIMEOUT ; 

__attribute__((used)) static int
savage_bci_wait_event_shadow(drm_savage_private_t * dev_priv, uint16_t e)
{
	uint32_t status;
	int i;

	for (i = 0; i < SAVAGE_EVENT_USEC_TIMEOUT; i++) {
		DRM_MEMORYBARRIER();
		status = dev_priv->status_ptr[1];
		if ((((status & 0xffff) - e) & 0xffff) <= 0x7fff ||
		    (status & 0xffff) == 0)
			return 0;
		DRM_UDELAY(1);
	}

#if SAVAGE_BCI_DEBUG
	DRM_ERROR("failed!\n");
	DRM_INFO("   status=0x%08x, e=0x%04x\n", status, e);
#endif

	return -EBUSY;
}