#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int list_count; int* ref_count; scalar_t__* nb_ref_modifications; TYPE_1__** ref_modifications; int /*<<< orphan*/  gb; } ;
struct TYPE_4__ {unsigned int op; int /*<<< orphan*/  val; } ;
typedef  TYPE_2__ H264SliceContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_ue_golomb_31 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ue_golomb_long (int /*<<< orphan*/ *) ; 

int ff_h264_decode_ref_pic_list_reordering(H264SliceContext *sl, void *logctx)
{
    int list, index;

    sl->nb_ref_modifications[0] = 0;
    sl->nb_ref_modifications[1] = 0;

    for (list = 0; list < sl->list_count; list++) {
        if (!get_bits1(&sl->gb))    // ref_pic_list_modification_flag_l[01]
            continue;

        for (index = 0; ; index++) {
            unsigned int op = get_ue_golomb_31(&sl->gb);

            if (op == 3)
                break;

            if (index >= sl->ref_count[list]) {
                av_log(logctx, AV_LOG_ERROR, "reference count overflow\n");
                return AVERROR_INVALIDDATA;
            } else if (op > 2) {
                av_log(logctx, AV_LOG_ERROR,
                       "illegal modification_of_pic_nums_idc %u\n",
                       op);
                return AVERROR_INVALIDDATA;
            }
            sl->ref_modifications[list][index].val = get_ue_golomb_long(&sl->gb);
            sl->ref_modifications[list][index].op  = op;
            sl->nb_ref_modifications[list]++;
        }
    }

    return 0;
}