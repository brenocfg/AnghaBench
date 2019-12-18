#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_12__ {scalar_t__ slice_type; int* nb_refs; int** list_entry_lx; size_t collocated_list; size_t collocated_ref_idx; scalar_t__* rpl_modification_flag; } ;
struct TYPE_14__ {TYPE_2__* ref; int /*<<< orphan*/  avctx; TYPE_4__* rps; TYPE_3__ sh; } ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {int nb_refs; int* isLongTerm; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * list; TYPE_1__ member_0; } ;
struct TYPE_11__ {int /*<<< orphan*/  collocated_ref; TYPE_4__* refPicList; } ;
typedef  TYPE_3__ SliceHeader ;
typedef  TYPE_4__ RefPicList ;
typedef  TYPE_5__ HEVCContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMIN (int,int) ; 
 int FF_ARRAY_ELEMS (int*) ; 
 int HEVC_MAX_REFS ; 
 scalar_t__ HEVC_SLICE_B ; 
 size_t LT_CURR ; 
 size_t ST_CURR_AFT ; 
 size_t ST_CURR_BEF ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int init_slice_rpl (TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 

int ff_hevc_slice_rpl(HEVCContext *s)
{
    SliceHeader *sh = &s->sh;

    uint8_t nb_list = sh->slice_type == HEVC_SLICE_B ? 2 : 1;
    uint8_t list_idx;
    int i, j, ret;

    ret = init_slice_rpl(s);
    if (ret < 0)
        return ret;

    if (!(s->rps[ST_CURR_BEF].nb_refs + s->rps[ST_CURR_AFT].nb_refs +
          s->rps[LT_CURR].nb_refs)) {
        av_log(s->avctx, AV_LOG_ERROR, "Zero refs in the frame RPS.\n");
        return AVERROR_INVALIDDATA;
    }

    for (list_idx = 0; list_idx < nb_list; list_idx++) {
        RefPicList  rpl_tmp = { { 0 } };
        RefPicList *rpl     = &s->ref->refPicList[list_idx];

        /* The order of the elements is
         * ST_CURR_BEF - ST_CURR_AFT - LT_CURR for the L0 and
         * ST_CURR_AFT - ST_CURR_BEF - LT_CURR for the L1 */
        int cand_lists[3] = { list_idx ? ST_CURR_AFT : ST_CURR_BEF,
                              list_idx ? ST_CURR_BEF : ST_CURR_AFT,
                              LT_CURR };

        /* concatenate the candidate lists for the current frame */
        while (rpl_tmp.nb_refs < sh->nb_refs[list_idx]) {
            for (i = 0; i < FF_ARRAY_ELEMS(cand_lists); i++) {
                RefPicList *rps = &s->rps[cand_lists[i]];
                for (j = 0; j < rps->nb_refs && rpl_tmp.nb_refs < HEVC_MAX_REFS; j++) {
                    rpl_tmp.list[rpl_tmp.nb_refs]       = rps->list[j];
                    rpl_tmp.ref[rpl_tmp.nb_refs]        = rps->ref[j];
                    rpl_tmp.isLongTerm[rpl_tmp.nb_refs] = i == 2;
                    rpl_tmp.nb_refs++;
                }
            }
        }

        /* reorder the references if necessary */
        if (sh->rpl_modification_flag[list_idx]) {
            for (i = 0; i < sh->nb_refs[list_idx]; i++) {
                int idx = sh->list_entry_lx[list_idx][i];

                if (idx >= rpl_tmp.nb_refs) {
                    av_log(s->avctx, AV_LOG_ERROR, "Invalid reference index.\n");
                    return AVERROR_INVALIDDATA;
                }

                rpl->list[i]       = rpl_tmp.list[idx];
                rpl->ref[i]        = rpl_tmp.ref[idx];
                rpl->isLongTerm[i] = rpl_tmp.isLongTerm[idx];
                rpl->nb_refs++;
            }
        } else {
            memcpy(rpl, &rpl_tmp, sizeof(*rpl));
            rpl->nb_refs = FFMIN(rpl->nb_refs, sh->nb_refs[list_idx]);
        }

        if (sh->collocated_list == list_idx &&
            sh->collocated_ref_idx < rpl->nb_refs)
            s->ref->collocated_ref = rpl->ref[sh->collocated_ref_idx];
    }

    return 0;
}