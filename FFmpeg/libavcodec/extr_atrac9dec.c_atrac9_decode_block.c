#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
struct TYPE_45__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_7__*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_44__ {int q_unit_cnt; int reuseable; int band_count; int band_ext_q_unit; int stereo_q_unit; int has_band_ext; int cpe_base_channel; int* is_signs; int q_unit_cnt_prev; TYPE_5__* channel; scalar_t__ has_band_ext_data; } ;
struct TYPE_43__ {int q_unit_cnt; int* scalefactors; int* q_coeffs_fine; int* q_coeffs_coarse; int* precision_coarse; int /*<<< orphan*/  prev_win; int /*<<< orphan*/  coeffs; scalar_t__* precision_fine; } ;
struct TYPE_42__ {int samplerate_idx; int frame_log2; scalar_t__ temp; int /*<<< orphan*/  imdct_win; TYPE_1__* fdsp; TYPE_7__ imdct; TYPE_2__* block_config; int /*<<< orphan*/  avctx; } ;
struct TYPE_41__ {scalar_t__* extended_data; } ;
struct TYPE_40__ {scalar_t__* type; int** plane_map; } ;
struct TYPE_39__ {int /*<<< orphan*/  (* vector_fmul_window ) (float*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int const) ;} ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ ATRAC9Context ;
typedef  TYPE_5__ ATRAC9ChannelData ;
typedef  TYPE_6__ ATRAC9BlockData ;

/* Variables and functions */
 scalar_t__ ATRAC9_BLOCK_TYPE_CPE ; 
 scalar_t__ ATRAC9_BLOCK_TYPE_LFE ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_ARRAY_ELEMS (int*) ; 
 int /*<<< orphan*/  apply_band_extension (TYPE_4__*,TYPE_6__*,int const) ; 
 int /*<<< orphan*/  apply_intensity_stereo (TYPE_4__*,TYPE_6__*,int const) ; 
 int /*<<< orphan*/  apply_scalefactors (TYPE_4__*,TYPE_6__*,int const) ; 
 int* at9_q_unit_to_coeff_idx ; 
 void** at9_tab_band_q_unit_map ; 
 size_t* at9_tab_sri_max_bands ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  calc_codebook_idx (TYPE_4__*,TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  calc_precision (TYPE_4__*,TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dequantize (TYPE_4__*,TYPE_6__*,TYPE_5__*) ; 
 int const get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_band_ext (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *,int const) ; 
 scalar_t__ parse_gradient (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_coeffs_coarse (TYPE_4__*,TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_coeffs_fine (TYPE_4__*,TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ read_scalefactors (TYPE_4__*,TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *,int,int const) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (float*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int atrac9_decode_block(ATRAC9Context *s, GetBitContext *gb,
                               ATRAC9BlockData *b, AVFrame *frame,
                               int frame_idx, int block_idx)
{
    const int first_in_pkt = !get_bits1(gb);
    const int reuse_params =  get_bits1(gb);
    const int stereo = s->block_config->type[block_idx] == ATRAC9_BLOCK_TYPE_CPE;

    if (s->block_config->type[block_idx] == ATRAC9_BLOCK_TYPE_LFE) {
        ATRAC9ChannelData *c = &b->channel[0];
        const int precision = reuse_params ? 8 : 4;
        c->q_unit_cnt = b->q_unit_cnt = 2;

        memset(c->scalefactors, 0, sizeof(c->scalefactors));
        memset(c->q_coeffs_fine, 0, sizeof(c->q_coeffs_fine));
        memset(c->q_coeffs_coarse, 0, sizeof(c->q_coeffs_coarse));

        for (int i = 0; i < b->q_unit_cnt; i++) {
            c->scalefactors[i] = get_bits(gb, 5);
            c->precision_coarse[i] = precision;
            c->precision_fine[i] = 0;
        }

        for (int i = 0; i < c->q_unit_cnt; i++) {
            const int start = at9_q_unit_to_coeff_idx[i + 0];
            const int end   = at9_q_unit_to_coeff_idx[i + 1];
            for (int j = start; j < end; j++)
                c->q_coeffs_coarse[j] = get_bits(gb, c->precision_coarse[i] + 1);
        }

        dequantize        (s, b, c);
        apply_scalefactors(s, b, 0);

        goto imdct;
    }

    if (first_in_pkt && reuse_params) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid block flags!\n");
        return AVERROR_INVALIDDATA;
    }

    /* Band parameters */
    if (!reuse_params) {
        int stereo_band, ext_band;
        const int min_band_count = s->samplerate_idx > 7 ? 1 : 3;
        b->reuseable = 0;
        b->band_count = get_bits(gb, 4) + min_band_count;
        b->q_unit_cnt = at9_tab_band_q_unit_map[b->band_count];

        b->band_ext_q_unit = b->stereo_q_unit = b->q_unit_cnt;

        if (b->band_count > at9_tab_sri_max_bands[s->samplerate_idx]) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid band count %i!\n",
                   b->band_count);
            return AVERROR_INVALIDDATA;
        }

        if (stereo) {
            stereo_band = get_bits(gb, 4) + min_band_count;
            if (stereo_band > b->band_count) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid stereo band %i!\n",
                       stereo_band);
                return AVERROR_INVALIDDATA;
            }
            b->stereo_q_unit = at9_tab_band_q_unit_map[stereo_band];
        }

        b->has_band_ext = get_bits1(gb);
        if (b->has_band_ext) {
            ext_band = get_bits(gb, 4) + min_band_count;
            if (ext_band < b->band_count) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid extension band %i!\n",
                       ext_band);
                return AVERROR_INVALIDDATA;
            }
            b->band_ext_q_unit = at9_tab_band_q_unit_map[ext_band];
        }
        b->reuseable = 1;
    }
    if (!b->reuseable) {
        av_log(s->avctx, AV_LOG_ERROR, "invalid block reused!\n");
        return AVERROR_INVALIDDATA;
    }

    /* Calculate bit alloc gradient */
    if (parse_gradient(s, b, gb))
        return AVERROR_INVALIDDATA;

    /* IS data */
    b->cpe_base_channel = 0;
    if (stereo) {
        b->cpe_base_channel = get_bits1(gb);
        if (get_bits1(gb)) {
            for (int i = b->stereo_q_unit; i < b->q_unit_cnt; i++)
                b->is_signs[i] = 1 - 2*get_bits1(gb);
        } else {
            for (int i = 0; i < FF_ARRAY_ELEMS(b->is_signs); i++)
                b->is_signs[i] = 1;
        }
    }

    /* Band extension */
    if (parse_band_ext(s, b, gb, stereo))
        return AVERROR_INVALIDDATA;

    /* Scalefactors */
    for (int i = 0; i <= stereo; i++) {
        ATRAC9ChannelData *c = &b->channel[i];
        c->q_unit_cnt = i == b->cpe_base_channel ? b->q_unit_cnt :
                                                   b->stereo_q_unit;
        if (read_scalefactors(s, b, c, gb, i, first_in_pkt))
            return AVERROR_INVALIDDATA;

        calc_precision    (s, b, c);
        calc_codebook_idx (s, b, c);
        read_coeffs_coarse(s, b, c, gb);
        read_coeffs_fine  (s, b, c, gb);
        dequantize        (s, b, c);
    }

    b->q_unit_cnt_prev = b->has_band_ext ? b->band_ext_q_unit : b->q_unit_cnt;

    apply_intensity_stereo(s, b, stereo);
    apply_scalefactors    (s, b, stereo);

    if (b->has_band_ext && b->has_band_ext_data)
        apply_band_extension  (s, b, stereo);

imdct:
    for (int i = 0; i <= stereo; i++) {
        ATRAC9ChannelData *c = &b->channel[i];
        const int dst_idx = s->block_config->plane_map[block_idx][i];
        const int wsize = 1 << s->frame_log2;
        const ptrdiff_t offset = wsize*frame_idx*sizeof(float);
        float *dst = (float *)(frame->extended_data[dst_idx] + offset);

        s->imdct.imdct_half(&s->imdct, s->temp, c->coeffs);
        s->fdsp->vector_fmul_window(dst, c->prev_win, s->temp,
                                    s->imdct_win, wsize >> 1);
        memcpy(c->prev_win, s->temp + (wsize >> 1), sizeof(float)*wsize >> 1);
    }

    return 0;
}