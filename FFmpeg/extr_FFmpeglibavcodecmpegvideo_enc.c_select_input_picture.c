#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_20__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_3__* f; } ;
struct TYPE_29__ {int num_entries; TYPE_1__* entry; } ;
struct TYPE_32__ {scalar_t__ picture_in_gop_number; scalar_t__ gop_size; int max_b_frames; int b_frame_strategy; int mb_num; int b_sensitivity; int mpv_flags; TYPE_12__ new_picture; int /*<<< orphan*/  picture_number; TYPE_4__* current_picture_ptr; TYPE_12__ current_picture; TYPE_11__* avctx; TYPE_4__** reordered_input_picture; TYPE_4__* picture; int /*<<< orphan*/  coded_picture_number; TYPE_4__** input_picture; int /*<<< orphan*/  linesize; TYPE_2__ rc_context; scalar_t__ intra_only; scalar_t__ next_picture_ptr; scalar_t__ frame_skip_factor; scalar_t__ frame_skip_threshold; } ;
struct TYPE_31__ {int b_frame_score; int reference; scalar_t__ shared; TYPE_20__* f; } ;
struct TYPE_30__ {int /*<<< orphan*/  display_picture_number; int /*<<< orphan*/ * data; } ;
struct TYPE_28__ {int pict_type; int display_picture_number; scalar_t__ coded_picture_number; int /*<<< orphan*/ * data; } ;
struct TYPE_27__ {int new_pict_type; } ;
struct TYPE_25__ {int flags; scalar_t__ rc_buffer_size; } ;
typedef  TYPE_4__ Picture ;
typedef  TYPE_5__ MpegEncContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_CLOSED_GOP ; 
 int AV_CODEC_FLAG_PASS2 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PICTURE_TYPE_B ; 
 void* AV_PICTURE_TYPE_I ; 
 void* AV_PICTURE_TYPE_P ; 
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 int FF_MPV_FLAG_STRICT_GOP ; 
 scalar_t__ INPLACE_OFFSET ; 
 int MAX_PICTURE_COUNT ; 
 scalar_t__ alloc_picture (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int av_frame_copy_props (TYPE_20__*,TYPE_20__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_20__*) ; 
 int /*<<< orphan*/  av_log (TYPE_11__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  emms_c () ; 
 int estimate_best_b_count (TYPE_5__*) ; 
 int ff_find_unused_picture (TYPE_11__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ff_mpeg_ref_picture (TYPE_11__*,TYPE_12__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ff_mpeg_unref_picture (TYPE_11__*,TYPE_12__*) ; 
 int /*<<< orphan*/  ff_vbv_update (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int get_intra_count (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_check (TYPE_5__*,TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int select_input_picture(MpegEncContext *s)
{
    int i, ret;

    for (i = 1; i < MAX_PICTURE_COUNT; i++)
        s->reordered_input_picture[i - 1] = s->reordered_input_picture[i];
    s->reordered_input_picture[MAX_PICTURE_COUNT - 1] = NULL;

    /* set next picture type & ordering */
    if (!s->reordered_input_picture[0] && s->input_picture[0]) {
        if (s->frame_skip_threshold || s->frame_skip_factor) {
            if (s->picture_in_gop_number < s->gop_size &&
                s->next_picture_ptr &&
                skip_check(s, s->input_picture[0], s->next_picture_ptr)) {
                // FIXME check that the gop check above is +-1 correct
                av_frame_unref(s->input_picture[0]->f);

                ff_vbv_update(s, 0);

                goto no_output_pic;
            }
        }

        if (/*s->picture_in_gop_number >= s->gop_size ||*/
            !s->next_picture_ptr || s->intra_only) {
            s->reordered_input_picture[0] = s->input_picture[0];
            s->reordered_input_picture[0]->f->pict_type = AV_PICTURE_TYPE_I;
            s->reordered_input_picture[0]->f->coded_picture_number =
                s->coded_picture_number++;
        } else {
            int b_frames = 0;

            if (s->avctx->flags & AV_CODEC_FLAG_PASS2) {
                for (i = 0; i < s->max_b_frames + 1; i++) {
                    int pict_num = s->input_picture[0]->f->display_picture_number + i;

                    if (pict_num >= s->rc_context.num_entries)
                        break;
                    if (!s->input_picture[i]) {
                        s->rc_context.entry[pict_num - 1].new_pict_type = AV_PICTURE_TYPE_P;
                        break;
                    }

                    s->input_picture[i]->f->pict_type =
                        s->rc_context.entry[pict_num].new_pict_type;
                }
            }

            if (s->b_frame_strategy == 0) {
                b_frames = s->max_b_frames;
                while (b_frames && !s->input_picture[b_frames])
                    b_frames--;
            } else if (s->b_frame_strategy == 1) {
                for (i = 1; i < s->max_b_frames + 1; i++) {
                    if (s->input_picture[i] &&
                        s->input_picture[i]->b_frame_score == 0) {
                        s->input_picture[i]->b_frame_score =
                            get_intra_count(s,
                                            s->input_picture[i    ]->f->data[0],
                                            s->input_picture[i - 1]->f->data[0],
                                            s->linesize) + 1;
                    }
                }
                for (i = 0; i < s->max_b_frames + 1; i++) {
                    if (!s->input_picture[i] ||
                        s->input_picture[i]->b_frame_score - 1 >
                            s->mb_num / s->b_sensitivity)
                        break;
                }

                b_frames = FFMAX(0, i - 1);

                /* reset scores */
                for (i = 0; i < b_frames + 1; i++) {
                    s->input_picture[i]->b_frame_score = 0;
                }
            } else if (s->b_frame_strategy == 2) {
                b_frames = estimate_best_b_count(s);
                if (b_frames < 0)
                    return b_frames;
            }

            emms_c();

            for (i = b_frames - 1; i >= 0; i--) {
                int type = s->input_picture[i]->f->pict_type;
                if (type && type != AV_PICTURE_TYPE_B)
                    b_frames = i;
            }
            if (s->input_picture[b_frames]->f->pict_type == AV_PICTURE_TYPE_B &&
                b_frames == s->max_b_frames) {
                av_log(s->avctx, AV_LOG_ERROR,
                       "warning, too many B-frames in a row\n");
            }

            if (s->picture_in_gop_number + b_frames >= s->gop_size) {
                if ((s->mpv_flags & FF_MPV_FLAG_STRICT_GOP) &&
                    s->gop_size > s->picture_in_gop_number) {
                    b_frames = s->gop_size - s->picture_in_gop_number - 1;
                } else {
                    if (s->avctx->flags & AV_CODEC_FLAG_CLOSED_GOP)
                        b_frames = 0;
                    s->input_picture[b_frames]->f->pict_type = AV_PICTURE_TYPE_I;
                }
            }

            if ((s->avctx->flags & AV_CODEC_FLAG_CLOSED_GOP) && b_frames &&
                s->input_picture[b_frames]->f->pict_type == AV_PICTURE_TYPE_I)
                b_frames--;

            s->reordered_input_picture[0] = s->input_picture[b_frames];
            if (s->reordered_input_picture[0]->f->pict_type != AV_PICTURE_TYPE_I)
                s->reordered_input_picture[0]->f->pict_type = AV_PICTURE_TYPE_P;
            s->reordered_input_picture[0]->f->coded_picture_number =
                s->coded_picture_number++;
            for (i = 0; i < b_frames; i++) {
                s->reordered_input_picture[i + 1] = s->input_picture[i];
                s->reordered_input_picture[i + 1]->f->pict_type =
                    AV_PICTURE_TYPE_B;
                s->reordered_input_picture[i + 1]->f->coded_picture_number =
                    s->coded_picture_number++;
            }
        }
    }
no_output_pic:
    ff_mpeg_unref_picture(s->avctx, &s->new_picture);

    if (s->reordered_input_picture[0]) {
        s->reordered_input_picture[0]->reference =
           s->reordered_input_picture[0]->f->pict_type !=
               AV_PICTURE_TYPE_B ? 3 : 0;

        if ((ret = ff_mpeg_ref_picture(s->avctx, &s->new_picture, s->reordered_input_picture[0])))
            return ret;

        if (s->reordered_input_picture[0]->shared || s->avctx->rc_buffer_size) {
            // input is a shared pix, so we can't modify it -> allocate a new
            // one & ensure that the shared one is reuseable

            Picture *pic;
            int i = ff_find_unused_picture(s->avctx, s->picture, 0);
            if (i < 0)
                return i;
            pic = &s->picture[i];

            pic->reference = s->reordered_input_picture[0]->reference;
            if (alloc_picture(s, pic, 0) < 0) {
                return -1;
            }

            ret = av_frame_copy_props(pic->f, s->reordered_input_picture[0]->f);
            if (ret < 0)
                return ret;

            /* mark us unused / free shared pic */
            av_frame_unref(s->reordered_input_picture[0]->f);
            s->reordered_input_picture[0]->shared = 0;

            s->current_picture_ptr = pic;
        } else {
            // input is not a shared pix -> reuse buffer for current_pix
            s->current_picture_ptr = s->reordered_input_picture[0];
            for (i = 0; i < 4; i++) {
                s->new_picture.f->data[i] += INPLACE_OFFSET;
            }
        }
        ff_mpeg_unref_picture(s->avctx, &s->current_picture);
        if ((ret = ff_mpeg_ref_picture(s->avctx, &s->current_picture,
                                       s->current_picture_ptr)) < 0)
            return ret;

        s->picture_number = s->new_picture.f->display_picture_number;
    }
    return 0;
}