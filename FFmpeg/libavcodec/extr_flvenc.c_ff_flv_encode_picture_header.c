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
typedef  int int64_t ;
struct TYPE_7__ {int h263_flv; int width; int height; scalar_t__ pict_type; int qscale; int /*<<< orphan*/  c_dc_scale_table; int /*<<< orphan*/  y_dc_scale_table; scalar_t__ h263_aic; int /*<<< orphan*/  pb; TYPE_2__* avctx; scalar_t__ picture_number; } ;
struct TYPE_5__ {int num; int den; } ;
struct TYPE_6__ {TYPE_1__ time_base; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  avpriv_align_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_aic_dc_scale_table ; 
 int /*<<< orphan*/  ff_mpeg1_dc_scale_table ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

void ff_flv_encode_picture_header(MpegEncContext *s, int picture_number)
{
    int format;

    avpriv_align_put_bits(&s->pb);

    put_bits(&s->pb, 17, 1);
    /* 0: H.263 escape codes 1: 11-bit escape codes */
    put_bits(&s->pb, 5, (s->h263_flv - 1));
    put_bits(&s->pb, 8,
             (((int64_t) s->picture_number * 30 * s->avctx->time_base.num) /   // FIXME use timestamp
              s->avctx->time_base.den) & 0xff);   /* TemporalReference */
    if (s->width == 352 && s->height == 288)
        format = 2;
    else if (s->width == 176 && s->height == 144)
        format = 3;
    else if (s->width == 128 && s->height == 96)
        format = 4;
    else if (s->width == 320 && s->height == 240)
        format = 5;
    else if (s->width == 160 && s->height == 120)
        format = 6;
    else if (s->width <= 255 && s->height <= 255)
        format = 0;   /* use 1 byte width & height */
    else
        format = 1;   /* use 2 bytes width & height */
    put_bits(&s->pb, 3, format);   /* PictureSize */
    if (format == 0) {
        put_bits(&s->pb, 8, s->width);
        put_bits(&s->pb, 8, s->height);
    } else if (format == 1) {
        put_bits(&s->pb, 16, s->width);
        put_bits(&s->pb, 16, s->height);
    }
    put_bits(&s->pb, 2, s->pict_type == AV_PICTURE_TYPE_P);   /* PictureType */
    put_bits(&s->pb, 1, 1);   /* DeblockingFlag: on */
    put_bits(&s->pb, 5, s->qscale);   /* Quantizer */
    put_bits(&s->pb, 1, 0);   /* ExtraInformation */

    if (s->h263_aic) {
        s->y_dc_scale_table =
        s->c_dc_scale_table = ff_aic_dc_scale_table;
    } else {
        s->y_dc_scale_table =
        s->c_dc_scale_table = ff_mpeg1_dc_scale_table;
    }
}