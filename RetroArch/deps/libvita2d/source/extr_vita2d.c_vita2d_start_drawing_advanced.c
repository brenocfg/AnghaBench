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
struct TYPE_3__ {int /*<<< orphan*/  gxm_sfd; int /*<<< orphan*/  gxm_sfc; int /*<<< orphan*/  gxm_rtgt; } ;
typedef  TYPE_1__ vita2d_texture ;

/* Variables and functions */
 int /*<<< orphan*/  _vita2d_context ; 
 size_t backBufferIndex ; 
 int /*<<< orphan*/  clip_rect_x_max ; 
 int /*<<< orphan*/  clip_rect_x_min ; 
 int /*<<< orphan*/  clip_rect_y_max ; 
 int /*<<< orphan*/  clip_rect_y_min ; 
 scalar_t__ clipping_enabled ; 
 int /*<<< orphan*/  depthSurface ; 
 int /*<<< orphan*/ ** displayBufferSync ; 
 int /*<<< orphan*/ * displaySurface ; 
 int drawing ; 
 int /*<<< orphan*/  renderTarget ; 
 int /*<<< orphan*/  sceGxmBeginScene (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vita2d_set_clip_rectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vita2d_start_drawing_advanced(vita2d_texture *target, unsigned int flags)
{

	if (target == NULL) {
		sceGxmBeginScene(
		_vita2d_context,
		flags,
		renderTarget,
		NULL,
		NULL,
		displayBufferSync[backBufferIndex],
		&displaySurface[backBufferIndex],
		&depthSurface);
	} else {
		sceGxmBeginScene(
		_vita2d_context,
		flags,
		target->gxm_rtgt,
		NULL,
		NULL,
		NULL,
		&target->gxm_sfc,
		&target->gxm_sfd);
	}

	drawing = 1;
	// in the current way, the library keeps the region clip across scenes
	if (clipping_enabled) {
		vita2d_set_clip_rectangle(clip_rect_x_min, clip_rect_y_min, clip_rect_x_max, clip_rect_y_max);
	}
}