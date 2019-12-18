#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
struct radeon_encoder_atom_dig {int /*<<< orphan*/  backlight_level; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct radeon_encoder {int devices; int encoder_id; struct radeon_encoder_atom_dig* enc_priv; struct drm_encoder base; } ;
struct TYPE_3__ {int firmware_flags; int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucAction; } ;
typedef  TYPE_2__ DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION ;

/* Variables and functions */
 int ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU ; 
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int /*<<< orphan*/  ATOM_LCD_BLOFF ; 
 int /*<<< orphan*/  ATOM_LCD_BLON ; 
 int /*<<< orphan*/  ATOM_LCD_BL_BRIGHTNESS_CONTROL ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_BL_BRIGHTNESS_CONTROL ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_LCD_BLOFF ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_LCD_BLON ; 
 int /*<<< orphan*/  COMMAND ; 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA 133 
#define  ENCODER_OBJECT_ID_INTERNAL_LVDS 132 
#define  ENCODER_OBJECT_ID_INTERNAL_LVTM1 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 128 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCD1OutputControl ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atombios_dig_transmitter_setup (struct drm_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atom_set_backlight_level_to_reg (struct radeon_device*,int /*<<< orphan*/ ) ; 

void
atombios_set_backlight_level(struct radeon_encoder *radeon_encoder, u8 level)
{
	struct drm_encoder *encoder = &radeon_encoder->base;
	struct drm_device *dev = radeon_encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder_atom_dig *dig;
	DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION args;
	int index;

	if (!(rdev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		return;

	if ((radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) &&
	    radeon_encoder->enc_priv) {
		dig = radeon_encoder->enc_priv;
		dig->backlight_level = level;
		radeon_atom_set_backlight_level_to_reg(rdev, dig->backlight_level);

		switch (radeon_encoder->encoder_id) {
		case ENCODER_OBJECT_ID_INTERNAL_LVDS:
		case ENCODER_OBJECT_ID_INTERNAL_LVTM1:
			index = GetIndexIntoMasterTable(COMMAND, LCD1OutputControl);
			if (dig->backlight_level == 0) {
				args.ucAction = ATOM_LCD_BLOFF;
				atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
			} else {
				args.ucAction = ATOM_LCD_BL_BRIGHTNESS_CONTROL;
				atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
				args.ucAction = ATOM_LCD_BLON;
				atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
			}
			break;
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
			if (dig->backlight_level == 0)
				atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_LCD_BLOFF, 0, 0);
			else {
				atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_BL_BRIGHTNESS_CONTROL, 0, 0);
				atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_LCD_BLON, 0, 0);
			}
			break;
		default:
			break;
		}
	}
}