#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VAAPIDecodePicture ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * hwaccel_picture_private; } ;
typedef  TYPE_1__ MJpegDecodeContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int ff_vaapi_decode_issue (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vaapi_mjpeg_end_frame(AVCodecContext *avctx)
{
    const MJpegDecodeContext *s = avctx->priv_data;
    VAAPIDecodePicture *pic = s->hwaccel_picture_private;

    return ff_vaapi_decode_issue(avctx, pic);
}