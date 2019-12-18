#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fbw_channels; int* first_cpl_coords; int num_cpl_bands; int** cpl_coords; scalar_t__ channel_mode; scalar_t__ phase_flags_in_use; scalar_t__* phase_flags; int /*<<< orphan*/  avctx; scalar_t__ eac3; scalar_t__* channel_in_cpl; int /*<<< orphan*/  gbc; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 scalar_t__ AC3_CHMODE_STEREO ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int coupling_coordinates(AC3DecodeContext *s, int blk)
{
    GetBitContext *bc = &s->gbc;
    int fbw_channels = s->fbw_channels;
    int ch, bnd;
    int cpl_coords_exist = 0;

    for (ch = 1; ch <= fbw_channels; ch++) {
        if (s->channel_in_cpl[ch]) {
            if ((s->eac3 && s->first_cpl_coords[ch]) || get_bits1(bc)) {
                int master_cpl_coord, cpl_coord_exp, cpl_coord_mant;
                s->first_cpl_coords[ch] = 0;
                cpl_coords_exist = 1;
                master_cpl_coord = 3 * get_bits(bc, 2);
                for (bnd = 0; bnd < s->num_cpl_bands; bnd++) {
                    cpl_coord_exp  = get_bits(bc, 4);
                    cpl_coord_mant = get_bits(bc, 4);
                    if (cpl_coord_exp == 15)
                        s->cpl_coords[ch][bnd] = cpl_coord_mant << 22;
                    else
                        s->cpl_coords[ch][bnd] = (cpl_coord_mant + 16) << 21;
                    s->cpl_coords[ch][bnd] >>= (cpl_coord_exp + master_cpl_coord);
                }
            } else if (!blk) {
                av_log(s->avctx, AV_LOG_ERROR, "new coupling coordinates must "
                       "be present in block 0\n");
                return AVERROR_INVALIDDATA;
            }
        } else {
            /* channel not in coupling */
            s->first_cpl_coords[ch] = 1;
        }
    }
    /* phase flags */
    if (s->channel_mode == AC3_CHMODE_STEREO && cpl_coords_exist) {
        for (bnd = 0; bnd < s->num_cpl_bands; bnd++) {
            s->phase_flags[bnd] = s->phase_flags_in_use ? get_bits1(bc) : 0;
        }
    }

    return 0;
}