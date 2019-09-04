#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* level_idc; } ;
struct TYPE_4__ {TYPE_3__* sub_layer_ptl; void** sub_layer_level_present_flag; void** sub_layer_profile_present_flag; TYPE_3__ general_ptl; } ;
typedef  TYPE_1__ PTL ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ decode_profile_tier_level (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_ptl(GetBitContext *gb, AVCodecContext *avctx,
                      PTL *ptl, int max_num_sub_layers)
{
    int i;
    if (decode_profile_tier_level(gb, avctx, &ptl->general_ptl) < 0 ||
        get_bits_left(gb) < 8 + (8*2 * (max_num_sub_layers - 1 > 0))) {
        av_log(avctx, AV_LOG_ERROR, "PTL information too short\n");
        return -1;
    }

    ptl->general_ptl.level_idc = get_bits(gb, 8);

    for (i = 0; i < max_num_sub_layers - 1; i++) {
        ptl->sub_layer_profile_present_flag[i] = get_bits1(gb);
        ptl->sub_layer_level_present_flag[i]   = get_bits1(gb);
    }

    if (max_num_sub_layers - 1> 0)
        for (i = max_num_sub_layers - 1; i < 8; i++)
            skip_bits(gb, 2); // reserved_zero_2bits[i]
    for (i = 0; i < max_num_sub_layers - 1; i++) {
        if (ptl->sub_layer_profile_present_flag[i] &&
            decode_profile_tier_level(gb, avctx, &ptl->sub_layer_ptl[i]) < 0) {
            av_log(avctx, AV_LOG_ERROR,
                   "PTL information for sublayer %i too short\n", i);
            return -1;
        }
        if (ptl->sub_layer_level_present_flag[i]) {
            if (get_bits_left(gb) < 8) {
                av_log(avctx, AV_LOG_ERROR,
                       "Not enough data for sublayer %i level_idc\n", i);
                return -1;
            } else
                ptl->sub_layer_ptl[i].level_idc = get_bits(gb, 8);
        }
    }

    return 0;
}