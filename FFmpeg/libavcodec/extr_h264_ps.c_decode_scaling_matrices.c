#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_6__ {scalar_t__ transform_8x8_mode; } ;
struct TYPE_5__ {int chroma_format_idc; int /*<<< orphan*/  const** scaling_matrix8; int /*<<< orphan*/  const** scaling_matrix4; scalar_t__ scaling_matrix_present; } ;
typedef  TYPE_1__ SPS ;
typedef  TYPE_2__ PPS ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int decode_scaling_list (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const** default_scaling4 ; 
 int /*<<< orphan*/  const** default_scaling8 ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_scaling_matrices(GetBitContext *gb, const SPS *sps,
                                    const PPS *pps, int is_sps,
                                    uint8_t(*scaling_matrix4)[16],
                                    uint8_t(*scaling_matrix8)[64])
{
    int fallback_sps = !is_sps && sps->scaling_matrix_present;
    const uint8_t *fallback[4] = {
        fallback_sps ? sps->scaling_matrix4[0] : default_scaling4[0],
        fallback_sps ? sps->scaling_matrix4[3] : default_scaling4[1],
        fallback_sps ? sps->scaling_matrix8[0] : default_scaling8[0],
        fallback_sps ? sps->scaling_matrix8[3] : default_scaling8[1]
    };
    int ret = 0;
    if (get_bits1(gb)) {
        ret |= decode_scaling_list(gb, scaling_matrix4[0], 16, default_scaling4[0], fallback[0]);        // Intra, Y
        ret |= decode_scaling_list(gb, scaling_matrix4[1], 16, default_scaling4[0], scaling_matrix4[0]); // Intra, Cr
        ret |= decode_scaling_list(gb, scaling_matrix4[2], 16, default_scaling4[0], scaling_matrix4[1]); // Intra, Cb
        ret |= decode_scaling_list(gb, scaling_matrix4[3], 16, default_scaling4[1], fallback[1]);        // Inter, Y
        ret |= decode_scaling_list(gb, scaling_matrix4[4], 16, default_scaling4[1], scaling_matrix4[3]); // Inter, Cr
        ret |= decode_scaling_list(gb, scaling_matrix4[5], 16, default_scaling4[1], scaling_matrix4[4]); // Inter, Cb
        if (is_sps || pps->transform_8x8_mode) {
            ret |= decode_scaling_list(gb, scaling_matrix8[0], 64, default_scaling8[0], fallback[2]); // Intra, Y
            ret |= decode_scaling_list(gb, scaling_matrix8[3], 64, default_scaling8[1], fallback[3]); // Inter, Y
            if (sps->chroma_format_idc == 3) {
                ret |= decode_scaling_list(gb, scaling_matrix8[1], 64, default_scaling8[0], scaling_matrix8[0]); // Intra, Cr
                ret |= decode_scaling_list(gb, scaling_matrix8[4], 64, default_scaling8[1], scaling_matrix8[3]); // Inter, Cr
                ret |= decode_scaling_list(gb, scaling_matrix8[2], 64, default_scaling8[0], scaling_matrix8[1]); // Intra, Cb
                ret |= decode_scaling_list(gb, scaling_matrix8[5], 64, default_scaling8[1], scaling_matrix8[4]); // Inter, Cb
            }
        }
        if (!ret)
            ret = is_sps;
    }

    return ret;
}