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
struct TYPE_3__ {int /*<<< orphan*/  saturation; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct TYPE_4__ {TYPE_1__ color_params; } ;
struct camera_data {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  cpia2_set_brightness (struct camera_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpia2_set_contrast (struct camera_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpia2_set_saturation (struct camera_data*,int /*<<< orphan*/ ) ; 

void cpia2_set_color_params(struct camera_data *cam)
{
	DBG("Setting color params\n");
	cpia2_set_brightness(cam, cam->params.color_params.brightness);
	cpia2_set_contrast(cam, cam->params.color_params.contrast);
	cpia2_set_saturation(cam, cam->params.color_params.saturation);
}