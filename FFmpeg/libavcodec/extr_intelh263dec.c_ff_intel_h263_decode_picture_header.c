#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int num; int den; } ;
struct TYPE_9__ {TYPE_4__ sample_aspect_ratio; int /*<<< orphan*/  lowres; } ;
struct TYPE_7__ {int picture_number; int h263_long_vectors; int obmc; int unrestricted_mv; int pb_frame; int loop_filter; int chroma_qscale; int qscale; int f_code; int /*<<< orphan*/  c_dc_scale_table; int /*<<< orphan*/  y_dc_scale_table; int /*<<< orphan*/  gb; TYPE_5__* avctx; void* height; void* width; scalar_t__ pict_type; scalar_t__ h263_plus; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int FRAME_SKIPPED ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int check_marker (TYPE_5__*,int /*<<< orphan*/ *,char*) ; 
 void*** ff_h263_format ; 
 TYPE_4__* ff_h263_pixel_aspect ; 
 int /*<<< orphan*/  ff_h263_show_pict_info (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_mpeg1_dc_scale_table ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 
 scalar_t__ skip_1stop_8data_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

int ff_intel_h263_decode_picture_header(MpegEncContext *s)
{
    int format;

    if (get_bits_left(&s->gb) == 64) { /* special dummy frames */
        return FRAME_SKIPPED;
    }

    /* picture header */
    if (get_bits_long(&s->gb, 22) != 0x20) {
        av_log(s->avctx, AV_LOG_ERROR, "Bad picture start code\n");
        return -1;
    }
    s->picture_number = get_bits(&s->gb, 8); /* picture timestamp */

    if (check_marker(s->avctx, &s->gb, "after picture_number") != 1) {
        return -1;      /* marker */
    }
    if (get_bits1(&s->gb) != 0) {
        av_log(s->avctx, AV_LOG_ERROR, "Bad H.263 id\n");
        return -1;      /* H.263 id */
    }
    skip_bits1(&s->gb);         /* split screen off */
    skip_bits1(&s->gb);         /* camera  off */
    skip_bits1(&s->gb);         /* freeze picture release off */

    format = get_bits(&s->gb, 3);
    if (format == 0 || format == 6) {
        av_log(s->avctx, AV_LOG_ERROR, "Intel H.263 free format not supported\n");
        return -1;
    }
    s->h263_plus = 0;

    s->pict_type = AV_PICTURE_TYPE_I + get_bits1(&s->gb);

    s->h263_long_vectors = get_bits1(&s->gb);

    if (get_bits1(&s->gb) != 0) {
        av_log(s->avctx, AV_LOG_ERROR, "SAC not supported\n");
        return -1;      /* SAC: off */
    }
    s->obmc= get_bits1(&s->gb);
    s->unrestricted_mv = s->obmc || s->h263_long_vectors;
    s->pb_frame = get_bits1(&s->gb);

    if (format < 6) {
        s->width = ff_h263_format[format][0];
        s->height = ff_h263_format[format][1];
        s->avctx->sample_aspect_ratio.num = 12;
        s->avctx->sample_aspect_ratio.den = 11;
    } else {
        format = get_bits(&s->gb, 3);
        if(format == 0 || format == 7){
            av_log(s->avctx, AV_LOG_ERROR, "Wrong Intel H.263 format\n");
            return -1;
        }
        if(get_bits(&s->gb, 2))
            av_log(s->avctx, AV_LOG_ERROR, "Bad value for reserved field\n");
        s->loop_filter = get_bits1(&s->gb) * !s->avctx->lowres;
        if(get_bits1(&s->gb))
            av_log(s->avctx, AV_LOG_ERROR, "Bad value for reserved field\n");
        if(get_bits1(&s->gb))
            s->pb_frame = 2;
        if(get_bits(&s->gb, 5))
            av_log(s->avctx, AV_LOG_ERROR, "Bad value for reserved field\n");
        if(get_bits(&s->gb, 5) != 1)
            av_log(s->avctx, AV_LOG_ERROR, "Invalid marker\n");
    }
    if(format == 6){
        int ar = get_bits(&s->gb, 4);
        skip_bits(&s->gb, 9); // display width
        check_marker(s->avctx, &s->gb, "in dimensions");
        skip_bits(&s->gb, 9); // display height
        if(ar == 15){
            s->avctx->sample_aspect_ratio.num = get_bits(&s->gb, 8); // aspect ratio - width
            s->avctx->sample_aspect_ratio.den = get_bits(&s->gb, 8); // aspect ratio - height
        } else {
            s->avctx->sample_aspect_ratio = ff_h263_pixel_aspect[ar];
        }
        if (s->avctx->sample_aspect_ratio.num == 0)
            av_log(s->avctx, AV_LOG_ERROR, "Invalid aspect ratio.\n");
    }

    s->chroma_qscale= s->qscale = get_bits(&s->gb, 5);
    skip_bits1(&s->gb); /* Continuous Presence Multipoint mode: off */

    if(s->pb_frame){
        skip_bits(&s->gb, 3); //temporal reference for B-frame
        skip_bits(&s->gb, 2); //dbquant
    }

    /* PEI */
    if (skip_1stop_8data_bits(&s->gb) < 0)
        return AVERROR_INVALIDDATA;
    s->f_code = 1;

    s->y_dc_scale_table=
    s->c_dc_scale_table= ff_mpeg1_dc_scale_table;

    ff_h263_show_pict_info(s);

    return 0;
}