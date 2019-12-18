#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_19__ {scalar_t__ display_picture_number; int /*<<< orphan*/ * data; } ;
struct TYPE_18__ {TYPE_7__* avframe; } ;
struct TYPE_17__ {unsigned int frame_number; int num_refs; TYPE_5__** ref_frames; int /*<<< orphan*/  avctx; TYPE_13__* current_picture; TYPE_5__** ref_pics; TYPE_5__* all_frames; int /*<<< orphan*/  gb; } ;
struct TYPE_16__ {int /*<<< orphan*/  reference; } ;
struct TYPE_15__ {unsigned int display_picture_number; } ;
struct TYPE_14__ {scalar_t__ reference; TYPE_1__* avframe; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ DiracFrame ;
typedef  TYPE_3__ DiracContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DELAYED_PIC_REF ; 
 scalar_t__ FFABS (scalar_t__) ; 
 scalar_t__ INT64_MAX ; 
 int MAX_FRAMES ; 
 int MAX_REFERENCE_FRAMES ; 
 scalar_t__ add_frame (TYPE_5__**,int,TYPE_13__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 unsigned int dirac_get_se_golomb (int /*<<< orphan*/ *) ; 
 int dirac_unpack_block_motion_data (TYPE_3__*) ; 
 int dirac_unpack_idwt_params (TYPE_3__*) ; 
 int dirac_unpack_prediction_parameters (TYPE_3__*) ; 
 unsigned int get_bits_long (int /*<<< orphan*/ *,int) ; 
 int get_buffer_with_edge (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_planes (TYPE_3__*) ; 
 TYPE_2__* remove_frame (TYPE_5__**,unsigned int) ; 

__attribute__((used)) static int dirac_decode_picture_header(DiracContext *s)
{
    unsigned retire, picnum;
    int i, j, ret;
    int64_t refdist, refnum;
    GetBitContext *gb = &s->gb;

    /* [DIRAC_STD] 11.1.1 Picture Header. picture_header() PICTURE_NUM */
    picnum = s->current_picture->avframe->display_picture_number = get_bits_long(gb, 32);


    av_log(s->avctx,AV_LOG_DEBUG,"PICTURE_NUM: %d\n",picnum);

    /* if this is the first keyframe after a sequence header, start our
       reordering from here */
    if (s->frame_number < 0)
        s->frame_number = picnum;

    s->ref_pics[0] = s->ref_pics[1] = NULL;
    for (i = 0; i < s->num_refs; i++) {
        refnum = (picnum + dirac_get_se_golomb(gb)) & 0xFFFFFFFF;
        refdist = INT64_MAX;

        /* find the closest reference to the one we want */
        /* Jordi: this is needed if the referenced picture hasn't yet arrived */
        for (j = 0; j < MAX_REFERENCE_FRAMES && refdist; j++)
            if (s->ref_frames[j]
                && FFABS(s->ref_frames[j]->avframe->display_picture_number - refnum) < refdist) {
                s->ref_pics[i] = s->ref_frames[j];
                refdist = FFABS(s->ref_frames[j]->avframe->display_picture_number - refnum);
            }

        if (!s->ref_pics[i] || refdist)
            av_log(s->avctx, AV_LOG_DEBUG, "Reference not found\n");

        /* if there were no references at all, allocate one */
        if (!s->ref_pics[i])
            for (j = 0; j < MAX_FRAMES; j++)
                if (!s->all_frames[j].avframe->data[0]) {
                    s->ref_pics[i] = &s->all_frames[j];
                    ret = get_buffer_with_edge(s->avctx, s->ref_pics[i]->avframe, AV_GET_BUFFER_FLAG_REF);
                    if (ret < 0)
                        return ret;
                    break;
                }

        if (!s->ref_pics[i]) {
            av_log(s->avctx, AV_LOG_ERROR, "Reference could not be allocated\n");
            return AVERROR_INVALIDDATA;
        }

    }

    /* retire the reference frames that are not used anymore */
    if (s->current_picture->reference) {
        retire = (picnum + dirac_get_se_golomb(gb)) & 0xFFFFFFFF;
        if (retire != picnum) {
            DiracFrame *retire_pic = remove_frame(s->ref_frames, retire);

            if (retire_pic)
                retire_pic->reference &= DELAYED_PIC_REF;
            else
                av_log(s->avctx, AV_LOG_DEBUG, "Frame to retire not found\n");
        }

        /* if reference array is full, remove the oldest as per the spec */
        while (add_frame(s->ref_frames, MAX_REFERENCE_FRAMES, s->current_picture)) {
            av_log(s->avctx, AV_LOG_ERROR, "Reference frame overflow\n");
            remove_frame(s->ref_frames, s->ref_frames[0]->avframe->display_picture_number)->reference &= DELAYED_PIC_REF;
        }
    }

    if (s->num_refs) {
        ret = dirac_unpack_prediction_parameters(s);  /* [DIRAC_STD] 11.2 Picture Prediction Data. picture_prediction() */
        if (ret < 0)
            return ret;
        ret = dirac_unpack_block_motion_data(s);      /* [DIRAC_STD] 12. Block motion data syntax                       */
        if (ret < 0)
            return ret;
    }
    ret = dirac_unpack_idwt_params(s);                /* [DIRAC_STD] 11.3 Wavelet transform data                        */
    if (ret < 0)
        return ret;

    init_planes(s);
    return 0;
}