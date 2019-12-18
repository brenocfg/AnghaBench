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
struct st6422_settings {int /*<<< orphan*/  ctrls; } ;
struct TYPE_4__ {void* nctrls; void* ctrls; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrls; void* nmodes; void* cam_mode; } ;
struct TYPE_5__ {TYPE_3__ cam; } ;
struct sd {scalar_t__ bridge; struct st6422_settings* sensor_priv; TYPE_1__ desc; TYPE_2__ gspca_dev; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 scalar_t__ BRIDGE_ST6422 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  info (char*) ; 
 struct st6422_settings* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* st6422_ctrl ; 
 void* st6422_mode ; 

__attribute__((used)) static int st6422_probe(struct sd *sd)
{
	struct st6422_settings *sensor_settings;

	if (sd->bridge != BRIDGE_ST6422)
		return -ENODEV;

	info("st6422 sensor detected");

	sensor_settings = kmalloc(sizeof *sensor_settings, GFP_KERNEL);
	if (!sensor_settings)
		return -ENOMEM;

	sd->gspca_dev.cam.cam_mode = st6422_mode;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(st6422_mode);
	sd->gspca_dev.cam.ctrls = sensor_settings->ctrls;
	sd->desc.ctrls = st6422_ctrl;
	sd->desc.nctrls = ARRAY_SIZE(st6422_ctrl);
	sd->sensor_priv = sensor_settings;

	return 0;
}