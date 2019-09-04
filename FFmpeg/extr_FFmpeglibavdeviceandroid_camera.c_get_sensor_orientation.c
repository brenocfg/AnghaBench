#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * i32; int /*<<< orphan*/ * u8; } ;
struct TYPE_10__ {TYPE_1__ data; } ;
struct TYPE_9__ {TYPE_2__* priv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  sensor_orientation; int /*<<< orphan*/  lens_facing; int /*<<< orphan*/  camera_metadata; } ;
typedef  TYPE_2__ AndroidCameraCtx ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ ACameraMetadata_const_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ACAMERA_LENS_FACING ; 
 int /*<<< orphan*/  ACAMERA_SENSOR_ORIENTATION ; 
 int /*<<< orphan*/  ACameraMetadata_getConstEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void get_sensor_orientation(AVFormatContext *avctx)
{
    AndroidCameraCtx *ctx = avctx->priv_data;
    ACameraMetadata_const_entry lens_facing;
    ACameraMetadata_const_entry sensor_orientation;

    ACameraMetadata_getConstEntry(ctx->camera_metadata,
                                  ACAMERA_LENS_FACING, &lens_facing);
    ACameraMetadata_getConstEntry(ctx->camera_metadata,
                                  ACAMERA_SENSOR_ORIENTATION, &sensor_orientation);

    ctx->lens_facing = lens_facing.data.u8[0];
    ctx->sensor_orientation = sensor_orientation.data.i32[0];
}