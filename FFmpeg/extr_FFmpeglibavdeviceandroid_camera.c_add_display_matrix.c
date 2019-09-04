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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  display_matrix ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {scalar_t__ lens_facing; int /*<<< orphan*/  sensor_orientation; } ;
typedef  TYPE_1__ AndroidCameraCtx ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ ACAMERA_LENS_FACING_FRONT ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_DATA_DISPLAYMATRIX ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_display_matrix_flip (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_display_rotation_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_stream_new_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int add_display_matrix(AVFormatContext *avctx, AVStream *st)
{
    AndroidCameraCtx *ctx = avctx->priv_data;
    uint8_t *side_data;
    int32_t display_matrix[9];

    av_display_rotation_set(display_matrix, ctx->sensor_orientation);

    if (ctx->lens_facing == ACAMERA_LENS_FACING_FRONT) {
        av_display_matrix_flip(display_matrix, 1, 0);
    }

    side_data = av_stream_new_side_data(st,
            AV_PKT_DATA_DISPLAYMATRIX, sizeof(display_matrix));

    if (!side_data) {
        return AVERROR(ENOMEM);
    }

    memcpy(side_data, display_matrix, sizeof(display_matrix));

    return 0;
}