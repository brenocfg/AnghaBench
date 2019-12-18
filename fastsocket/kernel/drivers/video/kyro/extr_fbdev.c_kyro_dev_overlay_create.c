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
typedef  int u32 ;
struct TYPE_2__ {int ulOverlayOffset; int ulNextFreeVidMem; int ulOverlayStride; int ulOverlayUVStride; int /*<<< orphan*/  pSTGReg; } ;

/* Variables and functions */
 scalar_t__ CreateOverlaySurface (int /*<<< orphan*/ ,int,int,int,int,int*,int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GLOBAL_ALPHA ; 
 int /*<<< orphan*/  ResetOverlayRegisters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetOverlayBlendMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__ deviceInfo ; 

__attribute__((used)) static int kyro_dev_overlay_create(u32 ulWidth,
				   u32 ulHeight, int bLinear)
{
	u32 offset;
	u32 stride, uvStride;

	if (deviceInfo.ulOverlayOffset != 0)
		/*
		 * Can only create one overlay without resetting the card or
		 * changing display mode
		 */
		return -EINVAL;

	ResetOverlayRegisters(deviceInfo.pSTGReg);

	/* Overlays are addressed in multiples of 16bytes or 32bytes, so make
	 * sure the start offset is on an appropriate boundary.
	 */
	offset = deviceInfo.ulNextFreeVidMem;
	if ((offset & 0x1f) != 0) {
		offset = (offset + 32L) & 0xffffffE0L;
	}

	if (CreateOverlaySurface(deviceInfo.pSTGReg, ulWidth, ulHeight,
				 bLinear, offset, &stride, &uvStride) < 0)
		return -EINVAL;

	deviceInfo.ulOverlayOffset = offset;
	deviceInfo.ulOverlayStride = stride;
	deviceInfo.ulOverlayUVStride = uvStride;
	deviceInfo.ulNextFreeVidMem = offset + (ulHeight * stride) + (ulHeight * 2 * uvStride);

	SetOverlayBlendMode(deviceInfo.pSTGReg, GLOBAL_ALPHA, 0xf, 0x0);

	return 0;
}