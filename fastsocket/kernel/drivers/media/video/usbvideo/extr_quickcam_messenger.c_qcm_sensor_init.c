#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  whiteness; int /*<<< orphan*/  colour; int /*<<< orphan*/  hue; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct uvd {TYPE_1__ vpic; int /*<<< orphan*/  dev; scalar_t__ user_data; } ;
struct qcm {size_t size; } ;
struct TYPE_7__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {int reg; int val; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  CHECK_RET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISOC_PACKET_SIZE ; 
 int STV_ISO_ENABLE ; 
 TYPE_3__* camera_sizes ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_sensor_set_shutter (struct uvd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_sensor_setlevels (struct uvd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_sensor_setsize (struct uvd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_stv_setb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qcm_stv_setw (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* regval_table ; 

__attribute__((used)) static int qcm_sensor_init(struct uvd *uvd)
{
	struct qcm *cam = (struct qcm *) uvd->user_data;
	int ret;
	int i;

	for (i=0; i < ARRAY_SIZE(regval_table) ; i++) {
		CHECK_RET(ret, qcm_stv_setb(uvd->dev,
					regval_table[i].reg,
					regval_table[i].val));
	}

	CHECK_RET(ret, qcm_stv_setw(uvd->dev, 0x15c1,
				cpu_to_le16(ISOC_PACKET_SIZE)));
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x15c3, 0x08));
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x143f, 0x01));

	CHECK_RET(ret, qcm_stv_setb(uvd->dev, STV_ISO_ENABLE, 0x00));

	CHECK_RET(ret, qcm_sensor_setsize(uvd, camera_sizes[cam->size].cmd));

	CHECK_RET(ret, qcm_sensor_setlevels(uvd, uvd->vpic.brightness,
			uvd->vpic.contrast, uvd->vpic.hue, uvd->vpic.colour));

	CHECK_RET(ret, qcm_sensor_set_shutter(uvd, uvd->vpic.whiteness));
	CHECK_RET(ret, qcm_sensor_setsize(uvd, camera_sizes[cam->size].cmd));

	return 0;
}