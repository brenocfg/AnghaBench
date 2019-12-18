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
struct radeon_encoder_atom_dac {int tv_std; } ;
struct radeon_encoder {int encoder_id; int active_device; int pixel_clock; struct radeon_encoder_atom_dac* enc_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_5__ {int ucAction; int /*<<< orphan*/  usPixelClock; int /*<<< orphan*/  ucDacStandard; } ;
typedef  TYPE_2__ DAC_ENCODER_CONTROL_PS_ALLOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DAC1_CV ; 
 int /*<<< orphan*/  ATOM_DAC1_NTSC ; 
 int /*<<< orphan*/  ATOM_DAC1_PAL ; 
 int /*<<< orphan*/  ATOM_DAC1_PS2 ; 
 int ATOM_DEVICE_CRT_SUPPORT ; 
 int ATOM_DEVICE_CV_SUPPORT ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DAC1EncoderControl ; 
 int /*<<< orphan*/  DAC2EncoderControl ; 
#define  ENCODER_OBJECT_ID_INTERNAL_DAC1 139 
#define  ENCODER_OBJECT_ID_INTERNAL_DAC2 138 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1 137 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2 136 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TV_STD_NTSC 135 
#define  TV_STD_NTSC_J 134 
#define  TV_STD_PAL 133 
#define  TV_STD_PAL_60 132 
#define  TV_STD_PAL_CN 131 
#define  TV_STD_PAL_M 130 
#define  TV_STD_SCART_PAL 129 
#define  TV_STD_SECAM 128 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
atombios_dac_setup(struct drm_encoder *encoder, int action)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	DAC_ENCODER_CONTROL_PS_ALLOCATION args;
	int index = 0;
	struct radeon_encoder_atom_dac *dac_info = radeon_encoder->enc_priv;

	memset(&args, 0, sizeof(args));

	switch (radeon_encoder->encoder_id) {
	case ENCODER_OBJECT_ID_INTERNAL_DAC1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
		index = GetIndexIntoMasterTable(COMMAND, DAC1EncoderControl);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_DAC2:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		index = GetIndexIntoMasterTable(COMMAND, DAC2EncoderControl);
		break;
	}

	args.ucAction = action;

	if (radeon_encoder->active_device & (ATOM_DEVICE_CRT_SUPPORT))
		args.ucDacStandard = ATOM_DAC1_PS2;
	else if (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
		args.ucDacStandard = ATOM_DAC1_CV;
	else {
		switch (dac_info->tv_std) {
		case TV_STD_PAL:
		case TV_STD_PAL_M:
		case TV_STD_SCART_PAL:
		case TV_STD_SECAM:
		case TV_STD_PAL_CN:
			args.ucDacStandard = ATOM_DAC1_PAL;
			break;
		case TV_STD_NTSC:
		case TV_STD_NTSC_J:
		case TV_STD_PAL_60:
		default:
			args.ucDacStandard = ATOM_DAC1_NTSC;
			break;
		}
	}
	args.usPixelClock = cpu_to_le16(radeon_encoder->pixel_clock / 10);

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);

}