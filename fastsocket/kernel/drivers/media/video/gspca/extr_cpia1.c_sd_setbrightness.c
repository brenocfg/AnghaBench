#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  brightness; } ;
struct TYPE_4__ {int /*<<< orphan*/  allowableOverExposure; } ;
struct TYPE_6__ {TYPE_2__ colourParams; TYPE_1__ flickerControl; } ;
struct sd {TYPE_3__ params; } ;
struct gspca_dev {scalar_t__ streaming; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int command_setcolourparams (struct gspca_dev*) ; 
 int command_setflickerctrl (struct gspca_dev*) ; 
 int /*<<< orphan*/  find_over_exposure (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_setbrightness(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret;

	sd->params.colourParams.brightness = val;
	sd->params.flickerControl.allowableOverExposure =
		find_over_exposure(sd->params.colourParams.brightness);
	if (gspca_dev->streaming) {
		ret = command_setcolourparams(gspca_dev);
		if (ret)
			return ret;
		return command_setflickerctrl(gspca_dev);
	}
	return 0;
}