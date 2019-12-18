#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u32 ;
struct radeon_encoder {int encoder_id; int devices; int active_device; } ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_5__ {int /*<<< orphan*/  ucAction; } ;
typedef  TYPE_2__ DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION ;

/* Variables and functions */
 int ATOM_DEVICE_CV_SUPPORT ; 
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int /*<<< orphan*/  ATOM_LCD_BLOFF ; 
 int /*<<< orphan*/  ATOM_LCD_BLON ; 
 int ATOM_S3_DFP2I_ACTIVE ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  CV1OutputControl ; 
 int /*<<< orphan*/  DAC1OutputControl ; 
 int /*<<< orphan*/  DAC2OutputControl ; 
#define  DRM_MODE_DPMS_OFF 142 
#define  DRM_MODE_DPMS_ON 141 
#define  DRM_MODE_DPMS_STANDBY 140 
#define  DRM_MODE_DPMS_SUSPEND 139 
 int /*<<< orphan*/  DVOOutputControl ; 
#define  ENCODER_OBJECT_ID_INTERNAL_DAC1 138 
#define  ENCODER_OBJECT_ID_INTERNAL_DAC2 137 
#define  ENCODER_OBJECT_ID_INTERNAL_DDI 136 
#define  ENCODER_OBJECT_ID_INTERNAL_DVO1 135 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1 134 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2 133 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 132 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1 131 
#define  ENCODER_OBJECT_ID_INTERNAL_LVDS 130 
#define  ENCODER_OBJECT_ID_INTERNAL_LVTM1 129 
#define  ENCODER_OBJECT_ID_INTERNAL_TMDS1 128 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCD1OutputControl ; 
 int /*<<< orphan*/  LVTMAOutputControl ; 
 int /*<<< orphan*/  RADEON_BIOS_3_SCRATCH ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMDSAOutputControl ; 
 int /*<<< orphan*/  TV1OutputControl ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
radeon_atom_encoder_dpms_avivo(struct drm_encoder *encoder, int mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION args;
	int index = 0;

	memset(&args, 0, sizeof(args));

	switch (radeon_encoder->encoder_id) {
	case ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
		index = GetIndexIntoMasterTable(COMMAND, TMDSAOutputControl);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_DVO1:
	case ENCODER_OBJECT_ID_INTERNAL_DDI:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		index = GetIndexIntoMasterTable(COMMAND, DVOOutputControl);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_LVDS:
		index = GetIndexIntoMasterTable(COMMAND, LCD1OutputControl);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, LCD1OutputControl);
		else
			index = GetIndexIntoMasterTable(COMMAND, LVTMAOutputControl);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_DAC1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
		if (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, TV1OutputControl);
		else if (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, CV1OutputControl);
		else
			index = GetIndexIntoMasterTable(COMMAND, DAC1OutputControl);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_DAC2:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		if (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, TV1OutputControl);
		else if (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, CV1OutputControl);
		else
			index = GetIndexIntoMasterTable(COMMAND, DAC2OutputControl);
		break;
	default:
		return;
	}

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		args.ucAction = ATOM_ENABLE;
		/* workaround for DVOOutputControl on some RS690 systems */
		if (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DDI) {
			u32 reg = RREG32(RADEON_BIOS_3_SCRATCH);
			WREG32(RADEON_BIOS_3_SCRATCH, reg & ~ATOM_S3_DFP2I_ACTIVE);
			atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
			WREG32(RADEON_BIOS_3_SCRATCH, reg);
		} else
			atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
		if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) {
			args.ucAction = ATOM_LCD_BLON;
			atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
		}
		break;
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
	case DRM_MODE_DPMS_OFF:
		args.ucAction = ATOM_DISABLE;
		atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
		if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) {
			args.ucAction = ATOM_LCD_BLOFF;
			atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
		}
		break;
	}
}