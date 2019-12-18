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
struct uvd {scalar_t__ user_data; } ;
struct konicawc {int brightness; int white_bal; int contrast; int saturation; int sharpness; int lastframe; scalar_t__ buttonsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int,int) ; 
 int /*<<< orphan*/  SetBrightness ; 
 int /*<<< orphan*/  SetContrast ; 
 int /*<<< orphan*/  SetSaturation ; 
 int /*<<< orphan*/  SetSharpness ; 
 int /*<<< orphan*/  SetWhitebal ; 
 int /*<<< orphan*/  konicawc_set_camera_size (struct uvd*) ; 
 int /*<<< orphan*/  konicawc_set_value (struct uvd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int konicawc_setup_on_open(struct uvd *uvd)
{
	struct konicawc *cam = (struct konicawc *)uvd->user_data;

	DEBUG(1, "setting brightness to %d (%d)", cam->brightness,
	    cam->brightness * 11);
	konicawc_set_value(uvd, cam->brightness, SetBrightness);
	DEBUG(1, "setting white balance to %d (%d)", cam->white_bal,
	    cam->white_bal * 11);
	konicawc_set_value(uvd, cam->white_bal, SetWhitebal);
	DEBUG(1, "setting contrast to %d (%d)", cam->contrast,
	    cam->contrast * 11);
	konicawc_set_value(uvd, cam->contrast, SetContrast);
	DEBUG(1, "setting saturation to %d (%d)", cam->saturation,
	    cam->saturation * 11);
	konicawc_set_value(uvd, cam->saturation, SetSaturation);
	DEBUG(1, "setting sharpness to %d (%d)", cam->sharpness,
	    cam->sharpness * 11);
	konicawc_set_value(uvd, cam->sharpness, SetSharpness);
	konicawc_set_camera_size(uvd);
	cam->lastframe = -2;
	cam->buttonsts = 0;
	return 0;
}