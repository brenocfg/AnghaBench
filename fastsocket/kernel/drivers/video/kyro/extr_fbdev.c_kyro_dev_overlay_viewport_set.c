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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ ulOverlayOffset; int /*<<< orphan*/  pSTGReg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DisableRamdacOutput (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  EnableOverlayPlane (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableRamdacOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetOverlayViewPort (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_1__ deviceInfo ; 

__attribute__((used)) static int kyro_dev_overlay_viewport_set(u32 x, u32 y, u32 ulWidth, u32 ulHeight)
{
	if (deviceInfo.ulOverlayOffset == 0)
		/* probably haven't called CreateOverlay yet */
		return -EINVAL;

	/* Stop Ramdac Output */
	DisableRamdacOutput(deviceInfo.pSTGReg);

	SetOverlayViewPort(deviceInfo.pSTGReg,
			   x, y, x + ulWidth - 1, y + ulHeight - 1);

	EnableOverlayPlane(deviceInfo.pSTGReg);
	/* Start Ramdac Output */
	EnableRamdacOutput(deviceInfo.pSTGReg);

	return 0;
}