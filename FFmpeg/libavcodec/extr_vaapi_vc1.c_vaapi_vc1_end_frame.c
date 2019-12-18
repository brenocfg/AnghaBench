#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* avctx; TYPE_1__* current_picture_ptr; } ;
struct TYPE_11__ {TYPE_4__ s; } ;
typedef  TYPE_3__ VC1Context ;
typedef  int /*<<< orphan*/  VAAPIDecodePicture ;
struct TYPE_13__ {TYPE_3__* priv_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  height; } ;
struct TYPE_9__ {int /*<<< orphan*/ * hwaccel_picture_private; } ;
typedef  TYPE_4__ MpegEncContext ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_mpeg_draw_horiz_band (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_vaapi_decode_issue (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vaapi_vc1_end_frame(AVCodecContext *avctx)
{
    VC1Context *v = avctx->priv_data;
    MpegEncContext *s = &v->s;
    VAAPIDecodePicture *pic = s->current_picture_ptr->hwaccel_picture_private;
    int ret;

    ret = ff_vaapi_decode_issue(avctx, pic);
    if (ret < 0)
        goto fail;

    ff_mpeg_draw_horiz_band(s, 0, s->avctx->height);

fail:
    return ret;
}