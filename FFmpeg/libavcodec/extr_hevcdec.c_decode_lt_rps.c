#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_9__ {int pic_order_cnt_lsb; } ;
struct TYPE_8__ {TYPE_4__* sps; } ;
struct TYPE_12__ {int poc; TYPE_2__ sh; TYPE_1__ ps; } ;
struct TYPE_11__ {int log2_max_poc_lsb; unsigned int num_long_term_ref_pics_sps; int* lt_ref_pic_poc_lsb_sps; void** used_by_curr_pic_lt_sps_flag; int /*<<< orphan*/  long_term_ref_pics_present_flag; } ;
struct TYPE_10__ {unsigned int nb_refs; int* poc; void** used; } ;
typedef  TYPE_3__ LongTermRPS ;
typedef  TYPE_4__ HEVCSPS ;
typedef  TYPE_5__ HEVCContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ FF_ARRAY_ELEMS (int*) ; 
 int av_ceil_log2 (int) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 void* get_ue_golomb_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_lt_rps(HEVCContext *s, LongTermRPS *rps, GetBitContext *gb)
{
    const HEVCSPS *sps = s->ps.sps;
    int max_poc_lsb    = 1 << sps->log2_max_poc_lsb;
    int prev_delta_msb = 0;
    unsigned int nb_sps = 0, nb_sh;
    int i;

    rps->nb_refs = 0;
    if (!sps->long_term_ref_pics_present_flag)
        return 0;

    if (sps->num_long_term_ref_pics_sps > 0)
        nb_sps = get_ue_golomb_long(gb);
    nb_sh = get_ue_golomb_long(gb);

    if (nb_sps > sps->num_long_term_ref_pics_sps)
        return AVERROR_INVALIDDATA;
    if (nb_sh + (uint64_t)nb_sps > FF_ARRAY_ELEMS(rps->poc))
        return AVERROR_INVALIDDATA;

    rps->nb_refs = nb_sh + nb_sps;

    for (i = 0; i < rps->nb_refs; i++) {
        uint8_t delta_poc_msb_present;

        if (i < nb_sps) {
            uint8_t lt_idx_sps = 0;

            if (sps->num_long_term_ref_pics_sps > 1)
                lt_idx_sps = get_bits(gb, av_ceil_log2(sps->num_long_term_ref_pics_sps));

            rps->poc[i]  = sps->lt_ref_pic_poc_lsb_sps[lt_idx_sps];
            rps->used[i] = sps->used_by_curr_pic_lt_sps_flag[lt_idx_sps];
        } else {
            rps->poc[i]  = get_bits(gb, sps->log2_max_poc_lsb);
            rps->used[i] = get_bits1(gb);
        }

        delta_poc_msb_present = get_bits1(gb);
        if (delta_poc_msb_present) {
            int64_t delta = get_ue_golomb_long(gb);
            int64_t poc;

            if (i && i != nb_sps)
                delta += prev_delta_msb;

            poc = rps->poc[i] + s->poc - delta * max_poc_lsb - s->sh.pic_order_cnt_lsb;
            if (poc != (int32_t)poc)
                return AVERROR_INVALIDDATA;
            rps->poc[i] = poc;
            prev_delta_msb = delta;
        }
    }

    return 0;
}