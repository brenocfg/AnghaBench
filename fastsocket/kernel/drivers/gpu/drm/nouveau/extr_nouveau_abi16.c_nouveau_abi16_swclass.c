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
typedef  int u16 ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int card_type; } ;

/* Variables and functions */
#define  NV_04 136 
#define  NV_10 135 
#define  NV_20 134 
#define  NV_30 133 
#define  NV_40 132 
#define  NV_50 131 
#define  NV_C0 130 
#define  NV_D0 129 
#define  NV_E0 128 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 

u16
nouveau_abi16_swclass(struct nouveau_drm *drm)
{
	switch (nv_device(drm->device)->card_type) {
	case NV_04:
		return 0x006e;
	case NV_10:
	case NV_20:
	case NV_30:
	case NV_40:
		return 0x016e;
	case NV_50:
		return 0x506e;
	case NV_C0:
	case NV_D0:
	case NV_E0:
		return 0x906e;
	}

	return 0x0000;
}