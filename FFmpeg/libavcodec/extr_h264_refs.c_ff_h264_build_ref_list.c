#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_29__ {scalar_t__ pic_id; int reference; TYPE_3__* parent; int /*<<< orphan*/  poc; } ;
struct TYPE_28__ {TYPE_7__* default_ref; int /*<<< orphan*/ * last_pocs; int /*<<< orphan*/  avctx; TYPE_5__** long_ref; TYPE_5__** short_ref; int /*<<< orphan*/  short_ref_count; } ;
struct TYPE_27__ {int reference; int long_ref; int frame_num; int pic_id; } ;
struct TYPE_26__ {int list_count; int curr_pic_num; int* nb_ref_modifications; unsigned int const max_pic_num; int* ref_count; TYPE_7__** ref_list; TYPE_2__** ref_modifications; } ;
struct TYPE_25__ {scalar_t__ long_ref; TYPE_1__* f; } ;
struct TYPE_24__ {unsigned int op; unsigned int val; } ;
struct TYPE_23__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_4__ H264SliceContext ;
typedef  TYPE_5__ H264Picture ;
typedef  TYPE_6__ H264Context ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 scalar_t__ FIELD_PICTURE (TYPE_6__*) ; 
 scalar_t__ FRAME_MBAFF (TYPE_6__*) ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ av_buffer_get_ref_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  h264_fill_mbaff_ref_list (TYPE_4__*) ; 
 int /*<<< orphan*/  h264_initialise_ref_list (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mismatches_ref (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  pic_as_field (TYPE_7__*,int) ; 
 int pic_num_extract (TYPE_6__*,unsigned int,int*) ; 
 int /*<<< orphan*/  print_long_term (TYPE_6__*) ; 
 int /*<<< orphan*/  print_short_term (TYPE_6__*) ; 
 int /*<<< orphan*/  ref_from_h264pic (TYPE_7__*,TYPE_5__*) ; 

int ff_h264_build_ref_list(H264Context *h, H264SliceContext *sl)
{
    int list, index, pic_structure;

    print_short_term(h);
    print_long_term(h);

    h264_initialise_ref_list(h, sl);

    for (list = 0; list < sl->list_count; list++) {
        int pred = sl->curr_pic_num;

        for (index = 0; index < sl->nb_ref_modifications[list]; index++) {
            unsigned int modification_of_pic_nums_idc = sl->ref_modifications[list][index].op;
            unsigned int                          val = sl->ref_modifications[list][index].val;
            unsigned int pic_id;
            int i;
            H264Picture *ref = NULL;

            switch (modification_of_pic_nums_idc) {
            case 0:
            case 1: {
                const unsigned int abs_diff_pic_num = val + 1;
                int frame_num;

                if (abs_diff_pic_num > sl->max_pic_num) {
                    av_log(h->avctx, AV_LOG_ERROR,
                           "abs_diff_pic_num overflow\n");
                    return AVERROR_INVALIDDATA;
                }

                if (modification_of_pic_nums_idc == 0)
                    pred -= abs_diff_pic_num;
                else
                    pred += abs_diff_pic_num;
                pred &= sl->max_pic_num - 1;

                frame_num = pic_num_extract(h, pred, &pic_structure);

                for (i = h->short_ref_count - 1; i >= 0; i--) {
                    ref = h->short_ref[i];
                    assert(ref->reference);
                    assert(!ref->long_ref);
                    if (ref->frame_num == frame_num &&
                        (ref->reference & pic_structure))
                        break;
                }
                if (i >= 0)
                    ref->pic_id = pred;
                break;
            }
            case 2: {
                int long_idx;
                pic_id = val; // long_term_pic_idx

                long_idx = pic_num_extract(h, pic_id, &pic_structure);

                if (long_idx > 31U) {
                    av_log(h->avctx, AV_LOG_ERROR,
                           "long_term_pic_idx overflow\n");
                    return AVERROR_INVALIDDATA;
                }
                ref = h->long_ref[long_idx];
                assert(!(ref && !ref->reference));
                if (ref && (ref->reference & pic_structure)) {
                    ref->pic_id = pic_id;
                    assert(ref->long_ref);
                    i = 0;
                } else {
                    i = -1;
                }
                break;
            }
            default:
                av_assert0(0);
            }

            if (i < 0 || mismatches_ref(h, ref)) {
                av_log(h->avctx, AV_LOG_ERROR,
                       i < 0 ? "reference picture missing during reorder\n" :
                               "mismatching reference\n"
                      );
                memset(&sl->ref_list[list][index], 0, sizeof(sl->ref_list[0][0])); // FIXME
            } else {
                for (i = index; i + 1 < sl->ref_count[list]; i++) {
                    if (sl->ref_list[list][i].parent &&
                        ref->long_ref == sl->ref_list[list][i].parent->long_ref &&
                        ref->pic_id   == sl->ref_list[list][i].pic_id)
                        break;
                }
                for (; i > index; i--) {
                    sl->ref_list[list][i] = sl->ref_list[list][i - 1];
                }
                ref_from_h264pic(&sl->ref_list[list][index], ref);
                if (FIELD_PICTURE(h)) {
                    pic_as_field(&sl->ref_list[list][index], pic_structure);
                }
            }
        }
    }
    for (list = 0; list < sl->list_count; list++) {
        for (index = 0; index < sl->ref_count[list]; index++) {
            if (   !sl->ref_list[list][index].parent
                || (!FIELD_PICTURE(h) && (sl->ref_list[list][index].reference&3) != 3)) {
                int i;
                av_log(h->avctx, AV_LOG_ERROR, "Missing reference picture, default is %d\n", h->default_ref[list].poc);
                for (i = 0; i < FF_ARRAY_ELEMS(h->last_pocs); i++)
                    h->last_pocs[i] = INT_MIN;
                if (h->default_ref[list].parent
                    && !(!FIELD_PICTURE(h) && (h->default_ref[list].reference&3) != 3))
                    sl->ref_list[list][index] = h->default_ref[list];
                else
                    return -1;
            }
            av_assert0(av_buffer_get_ref_count(sl->ref_list[list][index].parent->f->buf[0]) > 0);
        }
    }

    if (FRAME_MBAFF(h))
        h264_fill_mbaff_ref_list(sl);

    return 0;
}