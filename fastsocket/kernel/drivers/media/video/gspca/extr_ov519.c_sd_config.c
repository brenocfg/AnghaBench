#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_device_id {int driver_info; } ;
struct sd {int bridge; int invert_led; int /*<<< orphan*/  quality; int /*<<< orphan*/  ctrls; } ;
struct cam {int bulk; int reverse_alts; int /*<<< orphan*/  ctrls; void* nmodes; void* cam_mode; int /*<<< orphan*/  bulk_nurbs; int /*<<< orphan*/  bulk_size; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int BRIDGE_INVERT_LED ; 
 int BRIDGE_MASK ; 
#define  BRIDGE_OV511 134 
#define  BRIDGE_OV511PLUS 133 
#define  BRIDGE_OV518 132 
#define  BRIDGE_OV518PLUS 131 
#define  BRIDGE_OV519 130 
#define  BRIDGE_OVFX2 129 
#define  BRIDGE_W9968CF 128 
 int /*<<< orphan*/  MAX_NURBS ; 
 int /*<<< orphan*/  OVFX2_BULK_SIZE ; 
 int /*<<< orphan*/  QUALITY_DEF ; 
 void* ov511_vga_mode ; 
 void* ov518_vga_mode ; 
 void* ov519_vga_mode ; 
 void* w9968cf_vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam = &gspca_dev->cam;

	sd->bridge = id->driver_info & BRIDGE_MASK;
	sd->invert_led = (id->driver_info & BRIDGE_INVERT_LED) != 0;

	switch (sd->bridge) {
	case BRIDGE_OV511:
	case BRIDGE_OV511PLUS:
		cam->cam_mode = ov511_vga_mode;
		cam->nmodes = ARRAY_SIZE(ov511_vga_mode);
		break;
	case BRIDGE_OV518:
	case BRIDGE_OV518PLUS:
		cam->cam_mode = ov518_vga_mode;
		cam->nmodes = ARRAY_SIZE(ov518_vga_mode);
		break;
	case BRIDGE_OV519:
		cam->cam_mode = ov519_vga_mode;
		cam->nmodes = ARRAY_SIZE(ov519_vga_mode);
		sd->invert_led = !sd->invert_led;
		break;
	case BRIDGE_OVFX2:
		cam->cam_mode = ov519_vga_mode;
		cam->nmodes = ARRAY_SIZE(ov519_vga_mode);
		cam->bulk_size = OVFX2_BULK_SIZE;
		cam->bulk_nurbs = MAX_NURBS;
		cam->bulk = 1;
		break;
	case BRIDGE_W9968CF:
		cam->cam_mode = w9968cf_vga_mode;
		cam->nmodes = ARRAY_SIZE(w9968cf_vga_mode);
		cam->reverse_alts = 1;
		break;
	}

	gspca_dev->cam.ctrls = sd->ctrls;
	sd->quality = QUALITY_DEF;

	return 0;
}