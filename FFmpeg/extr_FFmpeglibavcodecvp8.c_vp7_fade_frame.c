#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
struct TYPE_15__ {int mb_width; int mb_height; TYPE_6__** framep; int /*<<< orphan*/  avctx; int /*<<< orphan*/  keyframe; } ;
typedef  TYPE_2__ VP8Context ;
struct TYPE_16__ {scalar_t__ end; scalar_t__ buffer; scalar_t__ bits; } ;
typedef  TYPE_3__ VP56RangeCoder ;
struct TYPE_14__ {TYPE_4__* f; } ;
struct TYPE_18__ {TYPE_1__ tf; } ;
struct TYPE_17__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ AVFrame ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 size_t VP56_FRAME_GOLDEN ; 
 size_t VP56_FRAME_PREVIOUS ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  copy_chroma (TYPE_4__*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  fade (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int vp8_alloc_frame (TYPE_2__*,TYPE_6__*,int) ; 
 TYPE_6__* vp8_find_free_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  vp8_rac_get_uint (TYPE_3__*,int) ; 

__attribute__((used)) static int vp7_fade_frame(VP8Context *s, VP56RangeCoder *c)
{
    int alpha = (int8_t) vp8_rac_get_uint(c, 8);
    int beta  = (int8_t) vp8_rac_get_uint(c, 8);
    int ret;

    if (c->end <= c->buffer && c->bits >= 0)
        return AVERROR_INVALIDDATA;

    if (!s->keyframe && (alpha || beta)) {
        int width  = s->mb_width * 16;
        int height = s->mb_height * 16;
        AVFrame *src, *dst;

        if (!s->framep[VP56_FRAME_PREVIOUS] ||
            !s->framep[VP56_FRAME_GOLDEN]) {
            av_log(s->avctx, AV_LOG_WARNING, "Discarding interframe without a prior keyframe!\n");
            return AVERROR_INVALIDDATA;
        }

        dst =
        src = s->framep[VP56_FRAME_PREVIOUS]->tf.f;

        /* preserve the golden frame, write a new previous frame */
        if (s->framep[VP56_FRAME_GOLDEN] == s->framep[VP56_FRAME_PREVIOUS]) {
            s->framep[VP56_FRAME_PREVIOUS] = vp8_find_free_buffer(s);
            if ((ret = vp8_alloc_frame(s, s->framep[VP56_FRAME_PREVIOUS], 1)) < 0)
                return ret;

            dst = s->framep[VP56_FRAME_PREVIOUS]->tf.f;

            copy_chroma(dst, src, width, height);
        }

        fade(dst->data[0], dst->linesize[0],
             src->data[0], src->linesize[0],
             width, height, alpha, beta);
    }

    return 0;
}