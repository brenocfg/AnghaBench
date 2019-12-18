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
struct mem_block {int dummy; } ;
struct TYPE_3__ {struct mem_block* fb_heap; struct mem_block* gart_heap; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
#define  RADEON_MEM_REGION_FB 129 
#define  RADEON_MEM_REGION_GART 128 

__attribute__((used)) static struct mem_block **get_heap(drm_radeon_private_t * dev_priv, int region)
{
	switch (region) {
	case RADEON_MEM_REGION_GART:
		return &dev_priv->gart_heap;
	case RADEON_MEM_REGION_FB:
		return &dev_priv->fb_heap;
	default:
		return NULL;
	}
}