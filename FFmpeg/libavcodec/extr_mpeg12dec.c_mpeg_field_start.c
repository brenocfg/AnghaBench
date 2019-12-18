#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_28__ {int flags2; int active_thread_type; int slice_flags; TYPE_4__* hwaccel; } ;
struct TYPE_27__ {int /*<<< orphan*/ * data; } ;
struct TYPE_26__ {int a53_caption_size; scalar_t__ has_afd; int /*<<< orphan*/  afd; scalar_t__ has_stereo3d; int /*<<< orphan*/  stereo3d; int /*<<< orphan*/ * a53_caption; int /*<<< orphan*/  pan_scan; } ;
struct TYPE_22__ {TYPE_1__* f; } ;
struct TYPE_25__ {long long mb_width; long long mb_height; scalar_t__ picture_structure; TYPE_3__* current_picture_ptr; TYPE_2__ current_picture; TYPE_8__* avctx; scalar_t__ progressive_frame; scalar_t__ top_field_first; scalar_t__ progressive_sequence; scalar_t__ repeat_first_field; scalar_t__ first_field; } ;
struct TYPE_24__ {int (* end_frame ) (TYPE_8__*) ;int (* start_frame ) (TYPE_8__*,int /*<<< orphan*/  const*,int) ;} ;
struct TYPE_23__ {TYPE_16__* f; } ;
struct TYPE_21__ {int /*<<< orphan*/ * data; } ;
struct TYPE_20__ {int repeat_pict; scalar_t__* linesize; int /*<<< orphan*/ * data; } ;
typedef  TYPE_5__ MpegEncContext ;
typedef  TYPE_6__ Mpeg1Context ;
typedef  int /*<<< orphan*/  AVStereo3D ;
typedef  TYPE_7__ AVFrameSideData ;
typedef  TYPE_8__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_CODEC_FLAG2_CHUNKS ; 
 int /*<<< orphan*/  AV_FRAME_DATA_A53_CC ; 
 int /*<<< orphan*/  AV_FRAME_DATA_AFD ; 
 int /*<<< orphan*/  AV_FRAME_DATA_PANSCAN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_THREAD_FRAME ; 
 scalar_t__ HAVE_THREADS ; 
 scalar_t__ PICT_BOTTOM_FIELD ; 
 scalar_t__ PICT_FRAME ; 
 int SLICE_FLAG_ALLOW_FIELD ; 
 TYPE_7__* av_frame_new_side_data (TYPE_16__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_stereo3d_create_side_data (TYPE_16__*) ; 
 int /*<<< orphan*/  ff_mpeg_er_frame_start (TYPE_5__*) ; 
 int ff_mpv_frame_start (TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ff_thread_finish_setup (TYPE_8__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int stub1 (TYPE_8__*) ; 
 int stub2 (TYPE_8__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int mpeg_field_start(MpegEncContext *s, const uint8_t *buf, int buf_size)
{
    AVCodecContext *avctx = s->avctx;
    Mpeg1Context *s1      = (Mpeg1Context *) s;
    int ret;

    if (!(avctx->flags2 & AV_CODEC_FLAG2_CHUNKS)) {
        if (s->mb_width * s->mb_height * 11LL / (33 * 2 * 8) > buf_size)
            return AVERROR_INVALIDDATA;
    }

    /* start frame decoding */
    if (s->first_field || s->picture_structure == PICT_FRAME) {
        AVFrameSideData *pan_scan;

        if ((ret = ff_mpv_frame_start(s, avctx)) < 0)
            return ret;

        ff_mpeg_er_frame_start(s);

        /* first check if we must repeat the frame */
        s->current_picture_ptr->f->repeat_pict = 0;
        if (s->repeat_first_field) {
            if (s->progressive_sequence) {
                if (s->top_field_first)
                    s->current_picture_ptr->f->repeat_pict = 4;
                else
                    s->current_picture_ptr->f->repeat_pict = 2;
            } else if (s->progressive_frame) {
                s->current_picture_ptr->f->repeat_pict = 1;
            }
        }

        pan_scan = av_frame_new_side_data(s->current_picture_ptr->f,
                                          AV_FRAME_DATA_PANSCAN,
                                          sizeof(s1->pan_scan));
        if (!pan_scan)
            return AVERROR(ENOMEM);
        memcpy(pan_scan->data, &s1->pan_scan, sizeof(s1->pan_scan));

        if (s1->a53_caption) {
            AVFrameSideData *sd = av_frame_new_side_data(
                s->current_picture_ptr->f, AV_FRAME_DATA_A53_CC,
                s1->a53_caption_size);
            if (sd)
                memcpy(sd->data, s1->a53_caption, s1->a53_caption_size);
            av_freep(&s1->a53_caption);
        }

        if (s1->has_stereo3d) {
            AVStereo3D *stereo = av_stereo3d_create_side_data(s->current_picture_ptr->f);
            if (!stereo)
                return AVERROR(ENOMEM);

            *stereo = s1->stereo3d;
            s1->has_stereo3d = 0;
        }

        if (s1->has_afd) {
            AVFrameSideData *sd =
                av_frame_new_side_data(s->current_picture_ptr->f,
                                       AV_FRAME_DATA_AFD, 1);
            if (!sd)
                return AVERROR(ENOMEM);

            *sd->data   = s1->afd;
            s1->has_afd = 0;
        }

        if (HAVE_THREADS && (avctx->active_thread_type & FF_THREAD_FRAME))
            ff_thread_finish_setup(avctx);
    } else { // second field
        int i;

        if (!s->current_picture_ptr) {
            av_log(s->avctx, AV_LOG_ERROR, "first field missing\n");
            return AVERROR_INVALIDDATA;
        }

        if (s->avctx->hwaccel &&
            (s->avctx->slice_flags & SLICE_FLAG_ALLOW_FIELD)) {
            if ((ret = s->avctx->hwaccel->end_frame(s->avctx)) < 0) {
                av_log(avctx, AV_LOG_ERROR,
                       "hardware accelerator failed to decode first field\n");
                return ret;
            }
        }

        for (i = 0; i < 4; i++) {
            s->current_picture.f->data[i] = s->current_picture_ptr->f->data[i];
            if (s->picture_structure == PICT_BOTTOM_FIELD)
                s->current_picture.f->data[i] +=
                    s->current_picture_ptr->f->linesize[i];
        }
    }

    if (avctx->hwaccel) {
        if ((ret = avctx->hwaccel->start_frame(avctx, buf, buf_size)) < 0)
            return ret;
    }

    return 0;
}