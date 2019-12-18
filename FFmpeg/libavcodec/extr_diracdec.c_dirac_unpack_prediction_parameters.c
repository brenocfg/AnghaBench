#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_7__ {int zrs_exp; int** zrs; int perspective_exp; void** perspective; void** pan_tilt; } ;
struct TYPE_6__ {int chroma_x_shift; int chroma_y_shift; int mv_precision; unsigned int num_refs; int weight_log2denom; int* weight; int /*<<< orphan*/  avctx; TYPE_3__* globalmc; scalar_t__ globalmc_flag; TYPE_1__* plane; int /*<<< orphan*/  gb; } ;
struct TYPE_5__ {int xblen; int yblen; int xbsep; int ybsep; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ DiracContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ FFMAX (int,int) ; 
 scalar_t__ MAX_BLOCKSIZE ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 void* dirac_get_se_golomb (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_interleaved_ue_golomb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dirac_unpack_prediction_parameters(DiracContext *s)
{
    static const uint8_t default_blen[] = { 4, 12, 16, 24 };

    GetBitContext *gb = &s->gb;
    unsigned idx, ref;

    align_get_bits(gb);
    /* [DIRAC_STD] 11.2.2 Block parameters. block_parameters() */
    /* Luma and Chroma are equal. 11.2.3 */
    idx = get_interleaved_ue_golomb(gb); /* [DIRAC_STD] index */

    if (idx > 4) {
        av_log(s->avctx, AV_LOG_ERROR, "Block prediction index too high\n");
        return AVERROR_INVALIDDATA;
    }

    if (idx == 0) {
        s->plane[0].xblen = get_interleaved_ue_golomb(gb);
        s->plane[0].yblen = get_interleaved_ue_golomb(gb);
        s->plane[0].xbsep = get_interleaved_ue_golomb(gb);
        s->plane[0].ybsep = get_interleaved_ue_golomb(gb);
    } else {
        /*[DIRAC_STD] preset_block_params(index). Table 11.1 */
        s->plane[0].xblen = default_blen[idx-1];
        s->plane[0].yblen = default_blen[idx-1];
        s->plane[0].xbsep = 4 * idx;
        s->plane[0].ybsep = 4 * idx;
    }
    /*[DIRAC_STD] 11.2.4 motion_data_dimensions()
      Calculated in function dirac_unpack_block_motion_data */

    if (s->plane[0].xblen % (1 << s->chroma_x_shift) != 0 ||
        s->plane[0].yblen % (1 << s->chroma_y_shift) != 0 ||
        !s->plane[0].xblen || !s->plane[0].yblen) {
        av_log(s->avctx, AV_LOG_ERROR,
               "invalid x/y block length (%d/%d) for x/y chroma shift (%d/%d)\n",
               s->plane[0].xblen, s->plane[0].yblen, s->chroma_x_shift, s->chroma_y_shift);
        return AVERROR_INVALIDDATA;
    }
    if (!s->plane[0].xbsep || !s->plane[0].ybsep || s->plane[0].xbsep < s->plane[0].xblen/2 || s->plane[0].ybsep < s->plane[0].yblen/2) {
        av_log(s->avctx, AV_LOG_ERROR, "Block separation too small\n");
        return AVERROR_INVALIDDATA;
    }
    if (s->plane[0].xbsep > s->plane[0].xblen || s->plane[0].ybsep > s->plane[0].yblen) {
        av_log(s->avctx, AV_LOG_ERROR, "Block separation greater than size\n");
        return AVERROR_INVALIDDATA;
    }
    if (FFMAX(s->plane[0].xblen, s->plane[0].yblen) > MAX_BLOCKSIZE) {
        av_log(s->avctx, AV_LOG_ERROR, "Unsupported large block size\n");
        return AVERROR_PATCHWELCOME;
    }

    /*[DIRAC_STD] 11.2.5 Motion vector precision. motion_vector_precision()
      Read motion vector precision */
    s->mv_precision = get_interleaved_ue_golomb(gb);
    if (s->mv_precision > 3) {
        av_log(s->avctx, AV_LOG_ERROR, "MV precision finer than eighth-pel\n");
        return AVERROR_INVALIDDATA;
    }

    /*[DIRAC_STD] 11.2.6 Global motion. global_motion()
      Read the global motion compensation parameters */
    s->globalmc_flag = get_bits1(gb);
    if (s->globalmc_flag) {
        memset(s->globalmc, 0, sizeof(s->globalmc));
        /* [DIRAC_STD] pan_tilt(gparams) */
        for (ref = 0; ref < s->num_refs; ref++) {
            if (get_bits1(gb)) {
                s->globalmc[ref].pan_tilt[0] = dirac_get_se_golomb(gb);
                s->globalmc[ref].pan_tilt[1] = dirac_get_se_golomb(gb);
            }
            /* [DIRAC_STD] zoom_rotate_shear(gparams)
               zoom/rotation/shear parameters */
            if (get_bits1(gb)) {
                s->globalmc[ref].zrs_exp   = get_interleaved_ue_golomb(gb);
                s->globalmc[ref].zrs[0][0] = dirac_get_se_golomb(gb);
                s->globalmc[ref].zrs[0][1] = dirac_get_se_golomb(gb);
                s->globalmc[ref].zrs[1][0] = dirac_get_se_golomb(gb);
                s->globalmc[ref].zrs[1][1] = dirac_get_se_golomb(gb);
            } else {
                s->globalmc[ref].zrs[0][0] = 1;
                s->globalmc[ref].zrs[1][1] = 1;
            }
            /* [DIRAC_STD] perspective(gparams) */
            if (get_bits1(gb)) {
                s->globalmc[ref].perspective_exp = get_interleaved_ue_golomb(gb);
                s->globalmc[ref].perspective[0]  = dirac_get_se_golomb(gb);
                s->globalmc[ref].perspective[1]  = dirac_get_se_golomb(gb);
            }
            if (s->globalmc[ref].perspective_exp + (uint64_t)s->globalmc[ref].zrs_exp > 30) {
                return AVERROR_INVALIDDATA;
            }

        }
    }

    /*[DIRAC_STD] 11.2.7 Picture prediction mode. prediction_mode()
      Picture prediction mode, not currently used. */
    if (get_interleaved_ue_golomb(gb)) {
        av_log(s->avctx, AV_LOG_ERROR, "Unknown picture prediction mode\n");
        return AVERROR_INVALIDDATA;
    }

    /* [DIRAC_STD] 11.2.8 Reference picture weight. reference_picture_weights()
       just data read, weight calculation will be done later on. */
    s->weight_log2denom = 1;
    s->weight[0]        = 1;
    s->weight[1]        = 1;

    if (get_bits1(gb)) {
        s->weight_log2denom = get_interleaved_ue_golomb(gb);
        if (s->weight_log2denom < 1 || s->weight_log2denom > 8) {
            av_log(s->avctx, AV_LOG_ERROR, "weight_log2denom unsupported or invalid\n");
            s->weight_log2denom = 1;
            return AVERROR_INVALIDDATA;
        }
        s->weight[0] = dirac_get_se_golomb(gb);
        if (s->num_refs == 2)
            s->weight[1] = dirac_get_se_golomb(gb);
    }
    return 0;
}