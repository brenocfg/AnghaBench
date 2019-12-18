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
struct TYPE_3__ {int /*<<< orphan*/  saturation; } ;
struct TYPE_4__ {TYPE_1__ colourParams; } ;
struct sd {TYPE_2__ params; } ;
struct gspca_dev {scalar_t__ streaming; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int command_setcolourparams (struct gspca_dev*) ; 

__attribute__((used)) static int sd_setsaturation(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->params.colourParams.saturation = val;
	if (gspca_dev->streaming)
		return command_setcolourparams(gspca_dev);

	return 0;
}