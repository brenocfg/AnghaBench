#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_2__ mode_info; } ;
struct radeon_crtc {int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  v_border; int /*<<< orphan*/  h_border; } ;
struct drm_display_mode {int flags; scalar_t__ crtc_vsync_start; scalar_t__ crtc_vsync_end; scalar_t__ crtc_vdisplay; scalar_t__ crtc_vtotal; scalar_t__ crtc_hsync_start; scalar_t__ crtc_hsync_end; scalar_t__ crtc_hdisplay; scalar_t__ crtc_htotal; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_5__ {void* usAccess; } ;
struct TYPE_7__ {int /*<<< orphan*/  ucCRTC; TYPE_1__ susModeMiscInfo; int /*<<< orphan*/  ucOverscanTop; int /*<<< orphan*/  ucOverscanBottom; int /*<<< orphan*/  ucOverscanLeft; int /*<<< orphan*/  ucOverscanRight; void* usV_SyncWidth; void* usV_SyncStart; void* usV_Disp; void* usV_Total; void* usH_SyncWidth; void* usH_SyncStart; void* usH_Disp; void* usH_Total; } ;
typedef  TYPE_3__ SET_CRTC_TIMING_PARAMETERS_PS_ALLOCATION ;

/* Variables and functions */
 scalar_t__ ATOM_COMPOSITESYNC ; 
 scalar_t__ ATOM_DOUBLE_CLOCK_MODE ; 
 scalar_t__ ATOM_HSYNC_POLARITY ; 
 scalar_t__ ATOM_INTERLACE ; 
 scalar_t__ ATOM_VSYNC_POLARITY ; 
 int /*<<< orphan*/  COMMAND ; 
 int DRM_MODE_FLAG_CSYNC ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCRTC_Timing ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void atombios_crtc_set_timing(struct drm_crtc *crtc,
				     struct drm_display_mode *mode)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	SET_CRTC_TIMING_PARAMETERS_PS_ALLOCATION args;
	int index = GetIndexIntoMasterTable(COMMAND, SetCRTC_Timing);
	u16 misc = 0;

	memset(&args, 0, sizeof(args));
	args.usH_Total = cpu_to_le16(mode->crtc_htotal);
	args.usH_Disp = cpu_to_le16(mode->crtc_hdisplay);
	args.usH_SyncStart = cpu_to_le16(mode->crtc_hsync_start);
	args.usH_SyncWidth =
		cpu_to_le16(mode->crtc_hsync_end - mode->crtc_hsync_start);
	args.usV_Total = cpu_to_le16(mode->crtc_vtotal);
	args.usV_Disp = cpu_to_le16(mode->crtc_vdisplay);
	args.usV_SyncStart = cpu_to_le16(mode->crtc_vsync_start);
	args.usV_SyncWidth =
		cpu_to_le16(mode->crtc_vsync_end - mode->crtc_vsync_start);

	args.ucOverscanRight = radeon_crtc->h_border;
	args.ucOverscanLeft = radeon_crtc->h_border;
	args.ucOverscanBottom = radeon_crtc->v_border;
	args.ucOverscanTop = radeon_crtc->v_border;

	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		misc |= ATOM_VSYNC_POLARITY;
	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		misc |= ATOM_HSYNC_POLARITY;
	if (mode->flags & DRM_MODE_FLAG_CSYNC)
		misc |= ATOM_COMPOSITESYNC;
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		misc |= ATOM_INTERLACE;
	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		misc |= ATOM_DOUBLE_CLOCK_MODE;

	args.susModeMiscInfo.usAccess = cpu_to_le16(misc);
	args.ucCRTC = radeon_crtc->crtc_id;

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
}