#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int ucAction; int /*<<< orphan*/  ucDVOConfig; void* usPixelClock; } ;
struct TYPE_11__ {int /*<<< orphan*/  ucAttribute; } ;
struct TYPE_12__ {TYPE_3__ sDigAttrib; } ;
struct TYPE_13__ {int ucAction; TYPE_4__ usDevAttr; int /*<<< orphan*/  ucDeviceType; void* usPixelClock; } ;
struct TYPE_14__ {TYPE_5__ sDVOEncoder; } ;
struct TYPE_9__ {int ucEnable; int /*<<< orphan*/  ucMisc; } ;
struct TYPE_10__ {TYPE_1__ sXTmdsEncoder; } ;
union dvo_encoder_control {TYPE_7__ dvo_v3; TYPE_6__ dvo; TYPE_2__ ext_tmds; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_encoder {int pixel_clock; } ;
struct TYPE_16__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {scalar_t__ family; TYPE_8__ mode_info; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DEVICE_DFP1_INDEX ; 
 int /*<<< orphan*/  ATOM_PANEL_MISC_888RGB ; 
 scalar_t__ CHIP_RV410 ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  DVOEncoderControl ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANEL_ENCODER_MISC_DUAL ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (union dvo_encoder_control*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_dig_monitor_is_duallink (struct drm_encoder*,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void
atombios_dvo_setup(struct drm_encoder *encoder, int action)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	union dvo_encoder_control args;
	int index = GetIndexIntoMasterTable(COMMAND, DVOEncoderControl);
	uint8_t frev, crev;

	memset(&args, 0, sizeof(args));

	if (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		return;

	/* some R4xx chips have the wrong frev */
	if (rdev->family <= CHIP_RV410)
		frev = 1;

	switch (frev) {
	case 1:
		switch (crev) {
		case 1:
			/* R4xx, R5xx */
			args.ext_tmds.sXTmdsEncoder.ucEnable = action;

			if (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_clock))
				args.ext_tmds.sXTmdsEncoder.ucMisc |= PANEL_ENCODER_MISC_DUAL;

			args.ext_tmds.sXTmdsEncoder.ucMisc |= ATOM_PANEL_MISC_888RGB;
			break;
		case 2:
			/* RS600/690/740 */
			args.dvo.sDVOEncoder.ucAction = action;
			args.dvo.sDVOEncoder.usPixelClock = cpu_to_le16(radeon_encoder->pixel_clock / 10);
			/* DFP1, CRT1, TV1 depending on the type of port */
			args.dvo.sDVOEncoder.ucDeviceType = ATOM_DEVICE_DFP1_INDEX;

			if (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_clock))
				args.dvo.sDVOEncoder.usDevAttr.sDigAttrib.ucAttribute |= PANEL_ENCODER_MISC_DUAL;
			break;
		case 3:
			/* R6xx */
			args.dvo_v3.ucAction = action;
			args.dvo_v3.usPixelClock = cpu_to_le16(radeon_encoder->pixel_clock / 10);
			args.dvo_v3.ucDVOConfig = 0; /* XXX */
			break;
		default:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			break;
		}
		break;
	default:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		break;
	}

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
}