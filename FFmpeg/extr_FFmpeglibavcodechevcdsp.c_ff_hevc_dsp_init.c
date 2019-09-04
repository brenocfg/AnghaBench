#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* hevc_v_loop_filter_chroma_c; void* hevc_h_loop_filter_chroma_c; void* hevc_v_loop_filter_luma_c; void* hevc_h_loop_filter_luma_c; void* hevc_v_loop_filter_chroma; void* hevc_h_loop_filter_chroma; void* hevc_v_loop_filter_luma; void* hevc_h_loop_filter_luma; void**** put_hevc_epel_bi_w; void**** put_hevc_epel_bi; void**** put_hevc_epel_uni_w; void**** put_hevc_epel_uni; void**** put_hevc_epel; void**** put_hevc_qpel_bi_w; void**** put_hevc_qpel_bi; void**** put_hevc_qpel_uni_w; void**** put_hevc_qpel_uni; void**** put_hevc_qpel; int /*<<< orphan*/ * sao_edge_restore; int /*<<< orphan*/ * sao_edge_filter; int /*<<< orphan*/ * sao_band_filter; int /*<<< orphan*/ * idct_dc; int /*<<< orphan*/ * idct; int /*<<< orphan*/  transform_4x4_luma; int /*<<< orphan*/  transform_rdpcm; int /*<<< orphan*/  dequant; int /*<<< orphan*/ * add_residual; int /*<<< orphan*/  put_pcm; } ;
typedef  TYPE_1__ HEVCDSPContext ;

/* Variables and functions */
 scalar_t__ ARCH_ARM ; 
 scalar_t__ ARCH_MIPS ; 
 scalar_t__ ARCH_PPC ; 
 scalar_t__ ARCH_X86 ; 
 int /*<<< orphan*/  add_residual16x16_10 ; 
 int /*<<< orphan*/  add_residual16x16_12 ; 
 int /*<<< orphan*/  add_residual16x16_8 ; 
 int /*<<< orphan*/  add_residual16x16_9 ; 
 int /*<<< orphan*/  add_residual32x32_10 ; 
 int /*<<< orphan*/  add_residual32x32_12 ; 
 int /*<<< orphan*/  add_residual32x32_8 ; 
 int /*<<< orphan*/  add_residual32x32_9 ; 
 int /*<<< orphan*/  add_residual4x4_10 ; 
 int /*<<< orphan*/  add_residual4x4_12 ; 
 int /*<<< orphan*/  add_residual4x4_8 ; 
 int /*<<< orphan*/  add_residual4x4_9 ; 
 int /*<<< orphan*/  add_residual8x8_10 ; 
 int /*<<< orphan*/  add_residual8x8_12 ; 
 int /*<<< orphan*/  add_residual8x8_8 ; 
 int /*<<< orphan*/  add_residual8x8_9 ; 
 int /*<<< orphan*/  dequant_10 ; 
 int /*<<< orphan*/  dequant_12 ; 
 int /*<<< orphan*/  dequant_8 ; 
 int /*<<< orphan*/  dequant_9 ; 
 int /*<<< orphan*/  ff_hevc_dsp_init_arm (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ff_hevc_dsp_init_mips (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ff_hevc_dsp_init_ppc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ff_hevc_dsp_init_x86 (TYPE_1__*,int) ; 
 void* hevc_h_loop_filter_chroma_10 ; 
 void* hevc_h_loop_filter_chroma_12 ; 
 void* hevc_h_loop_filter_chroma_8 ; 
 void* hevc_h_loop_filter_chroma_9 ; 
 void* hevc_h_loop_filter_luma_10 ; 
 void* hevc_h_loop_filter_luma_12 ; 
 void* hevc_h_loop_filter_luma_8 ; 
 void* hevc_h_loop_filter_luma_9 ; 
 void* hevc_v_loop_filter_chroma_10 ; 
 void* hevc_v_loop_filter_chroma_12 ; 
 void* hevc_v_loop_filter_chroma_8 ; 
 void* hevc_v_loop_filter_chroma_9 ; 
 void* hevc_v_loop_filter_luma_10 ; 
 void* hevc_v_loop_filter_luma_12 ; 
 void* hevc_v_loop_filter_luma_8 ; 
 void* hevc_v_loop_filter_luma_9 ; 
 int /*<<< orphan*/  idct_16x16_10 ; 
 int /*<<< orphan*/  idct_16x16_12 ; 
 int /*<<< orphan*/  idct_16x16_8 ; 
 int /*<<< orphan*/  idct_16x16_9 ; 
 int /*<<< orphan*/  idct_16x16_dc_10 ; 
 int /*<<< orphan*/  idct_16x16_dc_12 ; 
 int /*<<< orphan*/  idct_16x16_dc_8 ; 
 int /*<<< orphan*/  idct_16x16_dc_9 ; 
 int /*<<< orphan*/  idct_32x32_10 ; 
 int /*<<< orphan*/  idct_32x32_12 ; 
 int /*<<< orphan*/  idct_32x32_8 ; 
 int /*<<< orphan*/  idct_32x32_9 ; 
 int /*<<< orphan*/  idct_32x32_dc_10 ; 
 int /*<<< orphan*/  idct_32x32_dc_12 ; 
 int /*<<< orphan*/  idct_32x32_dc_8 ; 
 int /*<<< orphan*/  idct_32x32_dc_9 ; 
 int /*<<< orphan*/  idct_4x4_10 ; 
 int /*<<< orphan*/  idct_4x4_12 ; 
 int /*<<< orphan*/  idct_4x4_8 ; 
 int /*<<< orphan*/  idct_4x4_9 ; 
 int /*<<< orphan*/  idct_4x4_dc_10 ; 
 int /*<<< orphan*/  idct_4x4_dc_12 ; 
 int /*<<< orphan*/  idct_4x4_dc_8 ; 
 int /*<<< orphan*/  idct_4x4_dc_9 ; 
 int /*<<< orphan*/  idct_8x8_10 ; 
 int /*<<< orphan*/  idct_8x8_12 ; 
 int /*<<< orphan*/  idct_8x8_8 ; 
 int /*<<< orphan*/  idct_8x8_9 ; 
 int /*<<< orphan*/  idct_8x8_dc_10 ; 
 int /*<<< orphan*/  idct_8x8_dc_12 ; 
 int /*<<< orphan*/  idct_8x8_dc_8 ; 
 int /*<<< orphan*/  idct_8x8_dc_9 ; 
 void* put_hevc_epel_bi_h_10 ; 
 void* put_hevc_epel_bi_h_12 ; 
 void* put_hevc_epel_bi_h_8 ; 
 void* put_hevc_epel_bi_h_9 ; 
 void* put_hevc_epel_bi_hv_10 ; 
 void* put_hevc_epel_bi_hv_12 ; 
 void* put_hevc_epel_bi_hv_8 ; 
 void* put_hevc_epel_bi_hv_9 ; 
 void* put_hevc_epel_bi_v_10 ; 
 void* put_hevc_epel_bi_v_12 ; 
 void* put_hevc_epel_bi_v_8 ; 
 void* put_hevc_epel_bi_v_9 ; 
 void* put_hevc_epel_bi_w_h_10 ; 
 void* put_hevc_epel_bi_w_h_12 ; 
 void* put_hevc_epel_bi_w_h_8 ; 
 void* put_hevc_epel_bi_w_h_9 ; 
 void* put_hevc_epel_bi_w_hv_10 ; 
 void* put_hevc_epel_bi_w_hv_12 ; 
 void* put_hevc_epel_bi_w_hv_8 ; 
 void* put_hevc_epel_bi_w_hv_9 ; 
 void* put_hevc_epel_bi_w_v_10 ; 
 void* put_hevc_epel_bi_w_v_12 ; 
 void* put_hevc_epel_bi_w_v_8 ; 
 void* put_hevc_epel_bi_w_v_9 ; 
 void* put_hevc_epel_h_10 ; 
 void* put_hevc_epel_h_12 ; 
 void* put_hevc_epel_h_8 ; 
 void* put_hevc_epel_h_9 ; 
 void* put_hevc_epel_hv_10 ; 
 void* put_hevc_epel_hv_12 ; 
 void* put_hevc_epel_hv_8 ; 
 void* put_hevc_epel_hv_9 ; 
 void* put_hevc_epel_uni_h_10 ; 
 void* put_hevc_epel_uni_h_12 ; 
 void* put_hevc_epel_uni_h_8 ; 
 void* put_hevc_epel_uni_h_9 ; 
 void* put_hevc_epel_uni_hv_10 ; 
 void* put_hevc_epel_uni_hv_12 ; 
 void* put_hevc_epel_uni_hv_8 ; 
 void* put_hevc_epel_uni_hv_9 ; 
 void* put_hevc_epel_uni_v_10 ; 
 void* put_hevc_epel_uni_v_12 ; 
 void* put_hevc_epel_uni_v_8 ; 
 void* put_hevc_epel_uni_v_9 ; 
 void* put_hevc_epel_uni_w_h_10 ; 
 void* put_hevc_epel_uni_w_h_12 ; 
 void* put_hevc_epel_uni_w_h_8 ; 
 void* put_hevc_epel_uni_w_h_9 ; 
 void* put_hevc_epel_uni_w_hv_10 ; 
 void* put_hevc_epel_uni_w_hv_12 ; 
 void* put_hevc_epel_uni_w_hv_8 ; 
 void* put_hevc_epel_uni_w_hv_9 ; 
 void* put_hevc_epel_uni_w_v_10 ; 
 void* put_hevc_epel_uni_w_v_12 ; 
 void* put_hevc_epel_uni_w_v_8 ; 
 void* put_hevc_epel_uni_w_v_9 ; 
 void* put_hevc_epel_v_10 ; 
 void* put_hevc_epel_v_12 ; 
 void* put_hevc_epel_v_8 ; 
 void* put_hevc_epel_v_9 ; 
 void* put_hevc_pel_bi_pixels_10 ; 
 void* put_hevc_pel_bi_pixels_12 ; 
 void* put_hevc_pel_bi_pixels_8 ; 
 void* put_hevc_pel_bi_pixels_9 ; 
 void* put_hevc_pel_bi_w_pixels_10 ; 
 void* put_hevc_pel_bi_w_pixels_12 ; 
 void* put_hevc_pel_bi_w_pixels_8 ; 
 void* put_hevc_pel_bi_w_pixels_9 ; 
 void* put_hevc_pel_pixels_10 ; 
 void* put_hevc_pel_pixels_12 ; 
 void* put_hevc_pel_pixels_8 ; 
 void* put_hevc_pel_pixels_9 ; 
 void* put_hevc_pel_uni_pixels_10 ; 
 void* put_hevc_pel_uni_pixels_12 ; 
 void* put_hevc_pel_uni_pixels_8 ; 
 void* put_hevc_pel_uni_pixels_9 ; 
 void* put_hevc_pel_uni_w_pixels_10 ; 
 void* put_hevc_pel_uni_w_pixels_12 ; 
 void* put_hevc_pel_uni_w_pixels_8 ; 
 void* put_hevc_pel_uni_w_pixels_9 ; 
 void* put_hevc_qpel_bi_h_10 ; 
 void* put_hevc_qpel_bi_h_12 ; 
 void* put_hevc_qpel_bi_h_8 ; 
 void* put_hevc_qpel_bi_h_9 ; 
 void* put_hevc_qpel_bi_hv_10 ; 
 void* put_hevc_qpel_bi_hv_12 ; 
 void* put_hevc_qpel_bi_hv_8 ; 
 void* put_hevc_qpel_bi_hv_9 ; 
 void* put_hevc_qpel_bi_v_10 ; 
 void* put_hevc_qpel_bi_v_12 ; 
 void* put_hevc_qpel_bi_v_8 ; 
 void* put_hevc_qpel_bi_v_9 ; 
 void* put_hevc_qpel_bi_w_h_10 ; 
 void* put_hevc_qpel_bi_w_h_12 ; 
 void* put_hevc_qpel_bi_w_h_8 ; 
 void* put_hevc_qpel_bi_w_h_9 ; 
 void* put_hevc_qpel_bi_w_hv_10 ; 
 void* put_hevc_qpel_bi_w_hv_12 ; 
 void* put_hevc_qpel_bi_w_hv_8 ; 
 void* put_hevc_qpel_bi_w_hv_9 ; 
 void* put_hevc_qpel_bi_w_v_10 ; 
 void* put_hevc_qpel_bi_w_v_12 ; 
 void* put_hevc_qpel_bi_w_v_8 ; 
 void* put_hevc_qpel_bi_w_v_9 ; 
 void* put_hevc_qpel_h_10 ; 
 void* put_hevc_qpel_h_12 ; 
 void* put_hevc_qpel_h_8 ; 
 void* put_hevc_qpel_h_9 ; 
 void* put_hevc_qpel_hv_10 ; 
 void* put_hevc_qpel_hv_12 ; 
 void* put_hevc_qpel_hv_8 ; 
 void* put_hevc_qpel_hv_9 ; 
 void* put_hevc_qpel_uni_h_10 ; 
 void* put_hevc_qpel_uni_h_12 ; 
 void* put_hevc_qpel_uni_h_8 ; 
 void* put_hevc_qpel_uni_h_9 ; 
 void* put_hevc_qpel_uni_hv_10 ; 
 void* put_hevc_qpel_uni_hv_12 ; 
 void* put_hevc_qpel_uni_hv_8 ; 
 void* put_hevc_qpel_uni_hv_9 ; 
 void* put_hevc_qpel_uni_v_10 ; 
 void* put_hevc_qpel_uni_v_12 ; 
 void* put_hevc_qpel_uni_v_8 ; 
 void* put_hevc_qpel_uni_v_9 ; 
 void* put_hevc_qpel_uni_w_h_10 ; 
 void* put_hevc_qpel_uni_w_h_12 ; 
 void* put_hevc_qpel_uni_w_h_8 ; 
 void* put_hevc_qpel_uni_w_h_9 ; 
 void* put_hevc_qpel_uni_w_hv_10 ; 
 void* put_hevc_qpel_uni_w_hv_12 ; 
 void* put_hevc_qpel_uni_w_hv_8 ; 
 void* put_hevc_qpel_uni_w_hv_9 ; 
 void* put_hevc_qpel_uni_w_v_10 ; 
 void* put_hevc_qpel_uni_w_v_12 ; 
 void* put_hevc_qpel_uni_w_v_8 ; 
 void* put_hevc_qpel_uni_w_v_9 ; 
 void* put_hevc_qpel_v_10 ; 
 void* put_hevc_qpel_v_12 ; 
 void* put_hevc_qpel_v_8 ; 
 void* put_hevc_qpel_v_9 ; 
 int /*<<< orphan*/  put_pcm_10 ; 
 int /*<<< orphan*/  put_pcm_12 ; 
 int /*<<< orphan*/  put_pcm_8 ; 
 int /*<<< orphan*/  put_pcm_9 ; 
 int /*<<< orphan*/  sao_band_filter_10 ; 
 int /*<<< orphan*/  sao_band_filter_12 ; 
 int /*<<< orphan*/  sao_band_filter_8 ; 
 int /*<<< orphan*/  sao_band_filter_9 ; 
 int /*<<< orphan*/  sao_edge_filter_10 ; 
 int /*<<< orphan*/  sao_edge_filter_12 ; 
 int /*<<< orphan*/  sao_edge_filter_8 ; 
 int /*<<< orphan*/  sao_edge_filter_9 ; 
 int /*<<< orphan*/  sao_edge_restore_0_10 ; 
 int /*<<< orphan*/  sao_edge_restore_0_12 ; 
 int /*<<< orphan*/  sao_edge_restore_0_8 ; 
 int /*<<< orphan*/  sao_edge_restore_0_9 ; 
 int /*<<< orphan*/  sao_edge_restore_1_10 ; 
 int /*<<< orphan*/  sao_edge_restore_1_12 ; 
 int /*<<< orphan*/  sao_edge_restore_1_8 ; 
 int /*<<< orphan*/  sao_edge_restore_1_9 ; 
 int /*<<< orphan*/  transform_4x4_luma_10 ; 
 int /*<<< orphan*/  transform_4x4_luma_12 ; 
 int /*<<< orphan*/  transform_4x4_luma_8 ; 
 int /*<<< orphan*/  transform_4x4_luma_9 ; 
 int /*<<< orphan*/  transform_rdpcm_10 ; 
 int /*<<< orphan*/  transform_rdpcm_12 ; 
 int /*<<< orphan*/  transform_rdpcm_8 ; 
 int /*<<< orphan*/  transform_rdpcm_9 ; 

void ff_hevc_dsp_init(HEVCDSPContext *hevcdsp, int bit_depth)
{
#undef FUNC
#define FUNC(a, depth) a ## _ ## depth

#undef PEL_FUNC
#define PEL_FUNC(dst1, idx1, idx2, a, depth)                                   \
    for(i = 0 ; i < 10 ; i++)                                                  \
{                                                                              \
    hevcdsp->dst1[i][idx1][idx2] = a ## _ ## depth;                            \
}

#undef EPEL_FUNCS
#define EPEL_FUNCS(depth)                                                     \
    PEL_FUNC(put_hevc_epel, 0, 0, put_hevc_pel_pixels, depth);                \
    PEL_FUNC(put_hevc_epel, 0, 1, put_hevc_epel_h, depth);                    \
    PEL_FUNC(put_hevc_epel, 1, 0, put_hevc_epel_v, depth);                    \
    PEL_FUNC(put_hevc_epel, 1, 1, put_hevc_epel_hv, depth)

#undef EPEL_UNI_FUNCS
#define EPEL_UNI_FUNCS(depth)                                                 \
    PEL_FUNC(put_hevc_epel_uni, 0, 0, put_hevc_pel_uni_pixels, depth);        \
    PEL_FUNC(put_hevc_epel_uni, 0, 1, put_hevc_epel_uni_h, depth);            \
    PEL_FUNC(put_hevc_epel_uni, 1, 0, put_hevc_epel_uni_v, depth);            \
    PEL_FUNC(put_hevc_epel_uni, 1, 1, put_hevc_epel_uni_hv, depth);           \
    PEL_FUNC(put_hevc_epel_uni_w, 0, 0, put_hevc_pel_uni_w_pixels, depth);    \
    PEL_FUNC(put_hevc_epel_uni_w, 0, 1, put_hevc_epel_uni_w_h, depth);        \
    PEL_FUNC(put_hevc_epel_uni_w, 1, 0, put_hevc_epel_uni_w_v, depth);        \
    PEL_FUNC(put_hevc_epel_uni_w, 1, 1, put_hevc_epel_uni_w_hv, depth)

#undef EPEL_BI_FUNCS
#define EPEL_BI_FUNCS(depth)                                                \
    PEL_FUNC(put_hevc_epel_bi, 0, 0, put_hevc_pel_bi_pixels, depth);        \
    PEL_FUNC(put_hevc_epel_bi, 0, 1, put_hevc_epel_bi_h, depth);            \
    PEL_FUNC(put_hevc_epel_bi, 1, 0, put_hevc_epel_bi_v, depth);            \
    PEL_FUNC(put_hevc_epel_bi, 1, 1, put_hevc_epel_bi_hv, depth);           \
    PEL_FUNC(put_hevc_epel_bi_w, 0, 0, put_hevc_pel_bi_w_pixels, depth);    \
    PEL_FUNC(put_hevc_epel_bi_w, 0, 1, put_hevc_epel_bi_w_h, depth);        \
    PEL_FUNC(put_hevc_epel_bi_w, 1, 0, put_hevc_epel_bi_w_v, depth);        \
    PEL_FUNC(put_hevc_epel_bi_w, 1, 1, put_hevc_epel_bi_w_hv, depth)

#undef QPEL_FUNCS
#define QPEL_FUNCS(depth)                                                     \
    PEL_FUNC(put_hevc_qpel, 0, 0, put_hevc_pel_pixels, depth);                \
    PEL_FUNC(put_hevc_qpel, 0, 1, put_hevc_qpel_h, depth);                    \
    PEL_FUNC(put_hevc_qpel, 1, 0, put_hevc_qpel_v, depth);                    \
    PEL_FUNC(put_hevc_qpel, 1, 1, put_hevc_qpel_hv, depth)

#undef QPEL_UNI_FUNCS
#define QPEL_UNI_FUNCS(depth)                                                 \
    PEL_FUNC(put_hevc_qpel_uni, 0, 0, put_hevc_pel_uni_pixels, depth);        \
    PEL_FUNC(put_hevc_qpel_uni, 0, 1, put_hevc_qpel_uni_h, depth);            \
    PEL_FUNC(put_hevc_qpel_uni, 1, 0, put_hevc_qpel_uni_v, depth);            \
    PEL_FUNC(put_hevc_qpel_uni, 1, 1, put_hevc_qpel_uni_hv, depth);           \
    PEL_FUNC(put_hevc_qpel_uni_w, 0, 0, put_hevc_pel_uni_w_pixels, depth);    \
    PEL_FUNC(put_hevc_qpel_uni_w, 0, 1, put_hevc_qpel_uni_w_h, depth);        \
    PEL_FUNC(put_hevc_qpel_uni_w, 1, 0, put_hevc_qpel_uni_w_v, depth);        \
    PEL_FUNC(put_hevc_qpel_uni_w, 1, 1, put_hevc_qpel_uni_w_hv, depth)

#undef QPEL_BI_FUNCS
#define QPEL_BI_FUNCS(depth)                                                  \
    PEL_FUNC(put_hevc_qpel_bi, 0, 0, put_hevc_pel_bi_pixels, depth);          \
    PEL_FUNC(put_hevc_qpel_bi, 0, 1, put_hevc_qpel_bi_h, depth);              \
    PEL_FUNC(put_hevc_qpel_bi, 1, 0, put_hevc_qpel_bi_v, depth);              \
    PEL_FUNC(put_hevc_qpel_bi, 1, 1, put_hevc_qpel_bi_hv, depth);             \
    PEL_FUNC(put_hevc_qpel_bi_w, 0, 0, put_hevc_pel_bi_w_pixels, depth);      \
    PEL_FUNC(put_hevc_qpel_bi_w, 0, 1, put_hevc_qpel_bi_w_h, depth);          \
    PEL_FUNC(put_hevc_qpel_bi_w, 1, 0, put_hevc_qpel_bi_w_v, depth);          \
    PEL_FUNC(put_hevc_qpel_bi_w, 1, 1, put_hevc_qpel_bi_w_hv, depth)

#define HEVC_DSP(depth)                                                     \
    hevcdsp->put_pcm                = FUNC(put_pcm, depth);                 \
    hevcdsp->add_residual[0]        = FUNC(add_residual4x4, depth);         \
    hevcdsp->add_residual[1]        = FUNC(add_residual8x8, depth);         \
    hevcdsp->add_residual[2]        = FUNC(add_residual16x16, depth);       \
    hevcdsp->add_residual[3]        = FUNC(add_residual32x32, depth);       \
    hevcdsp->dequant                = FUNC(dequant, depth);                 \
    hevcdsp->transform_rdpcm        = FUNC(transform_rdpcm, depth);         \
    hevcdsp->transform_4x4_luma     = FUNC(transform_4x4_luma, depth);      \
    hevcdsp->idct[0]                = FUNC(idct_4x4, depth);                \
    hevcdsp->idct[1]                = FUNC(idct_8x8, depth);                \
    hevcdsp->idct[2]                = FUNC(idct_16x16, depth);              \
    hevcdsp->idct[3]                = FUNC(idct_32x32, depth);              \
                                                                            \
    hevcdsp->idct_dc[0]             = FUNC(idct_4x4_dc, depth);             \
    hevcdsp->idct_dc[1]             = FUNC(idct_8x8_dc, depth);             \
    hevcdsp->idct_dc[2]             = FUNC(idct_16x16_dc, depth);           \
    hevcdsp->idct_dc[3]             = FUNC(idct_32x32_dc, depth);           \
                                                                            \
    hevcdsp->sao_band_filter[0] =                                              \
    hevcdsp->sao_band_filter[1] =                                              \
    hevcdsp->sao_band_filter[2] =                                              \
    hevcdsp->sao_band_filter[3] =                                              \
    hevcdsp->sao_band_filter[4] = FUNC(sao_band_filter, depth);                \
    hevcdsp->sao_edge_filter[0] =                                              \
    hevcdsp->sao_edge_filter[1] =                                              \
    hevcdsp->sao_edge_filter[2] =                                              \
    hevcdsp->sao_edge_filter[3] =                                              \
    hevcdsp->sao_edge_filter[4] = FUNC(sao_edge_filter, depth);                \
    hevcdsp->sao_edge_restore[0] = FUNC(sao_edge_restore_0, depth);            \
    hevcdsp->sao_edge_restore[1] = FUNC(sao_edge_restore_1, depth);            \
                                                                               \
    QPEL_FUNCS(depth);                                                         \
    QPEL_UNI_FUNCS(depth);                                                     \
    QPEL_BI_FUNCS(depth);                                                      \
    EPEL_FUNCS(depth);                                                         \
    EPEL_UNI_FUNCS(depth);                                                     \
    EPEL_BI_FUNCS(depth);                                                      \
                                                                               \
    hevcdsp->hevc_h_loop_filter_luma     = FUNC(hevc_h_loop_filter_luma, depth);   \
    hevcdsp->hevc_v_loop_filter_luma     = FUNC(hevc_v_loop_filter_luma, depth);   \
    hevcdsp->hevc_h_loop_filter_chroma   = FUNC(hevc_h_loop_filter_chroma, depth); \
    hevcdsp->hevc_v_loop_filter_chroma   = FUNC(hevc_v_loop_filter_chroma, depth); \
    hevcdsp->hevc_h_loop_filter_luma_c   = FUNC(hevc_h_loop_filter_luma, depth);   \
    hevcdsp->hevc_v_loop_filter_luma_c   = FUNC(hevc_v_loop_filter_luma, depth);   \
    hevcdsp->hevc_h_loop_filter_chroma_c = FUNC(hevc_h_loop_filter_chroma, depth); \
    hevcdsp->hevc_v_loop_filter_chroma_c = FUNC(hevc_v_loop_filter_chroma, depth)
int i = 0;

    switch (bit_depth) {
    case 9:
        HEVC_DSP(9);
        break;
    case 10:
        HEVC_DSP(10);
        break;
    case 12:
        HEVC_DSP(12);
        break;
    default:
        HEVC_DSP(8);
        break;
    }

    if (ARCH_ARM)
        ff_hevc_dsp_init_arm(hevcdsp, bit_depth);
    if (ARCH_PPC)
        ff_hevc_dsp_init_ppc(hevcdsp, bit_depth);
    if (ARCH_X86)
        ff_hevc_dsp_init_x86(hevcdsp, bit_depth);
    if (ARCH_MIPS)
        ff_hevc_dsp_init_mips(hevcdsp, bit_depth);
}