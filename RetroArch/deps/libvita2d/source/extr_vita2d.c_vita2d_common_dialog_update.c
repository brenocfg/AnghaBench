#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  updateParam ;
struct TYPE_5__ {int /*<<< orphan*/  depthSurfaceData; int /*<<< orphan*/  colorSurfaceData; int /*<<< orphan*/  strideInPixels; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  surfaceType; int /*<<< orphan*/  colorFormat; } ;
struct TYPE_6__ {int /*<<< orphan*/  displaySyncObject; TYPE_1__ renderTarget; } ;
typedef  TYPE_2__ SceCommonDialogUpdateParam ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_COLOR_FORMAT ; 
 int /*<<< orphan*/  DISPLAY_HEIGHT ; 
 int /*<<< orphan*/  DISPLAY_STRIDE_IN_PIXELS ; 
 int /*<<< orphan*/  DISPLAY_WIDTH ; 
 int /*<<< orphan*/  SCE_GXM_COLOR_SURFACE_LINEAR ; 
 size_t backBufferIndex ; 
 int /*<<< orphan*/  depthBufferData ; 
 int /*<<< orphan*/ * displayBufferData ; 
 int /*<<< orphan*/ * displayBufferSync ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int sceCommonDialogUpdate (TYPE_2__*) ; 

int vita2d_common_dialog_update()
{
	SceCommonDialogUpdateParam updateParam;
	memset(&updateParam, 0, sizeof(updateParam));

	updateParam.renderTarget.colorFormat    = DISPLAY_COLOR_FORMAT;
	updateParam.renderTarget.surfaceType    = SCE_GXM_COLOR_SURFACE_LINEAR;
	updateParam.renderTarget.width          = DISPLAY_WIDTH;
	updateParam.renderTarget.height         = DISPLAY_HEIGHT;
	updateParam.renderTarget.strideInPixels = DISPLAY_STRIDE_IN_PIXELS;

	updateParam.renderTarget.colorSurfaceData = displayBufferData[backBufferIndex];
	updateParam.renderTarget.depthSurfaceData = depthBufferData;
	updateParam.displaySyncObject = displayBufferSync[backBufferIndex];

	return sceCommonDialogUpdate(&updateParam);
}