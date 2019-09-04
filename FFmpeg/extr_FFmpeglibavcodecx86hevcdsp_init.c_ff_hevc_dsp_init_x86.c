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
struct TYPE_3__ {int /*<<< orphan*/ * idct_dc; int /*<<< orphan*/ * sao_band_filter; int /*<<< orphan*/  hevc_h_loop_filter_luma; int /*<<< orphan*/  hevc_v_loop_filter_luma; int /*<<< orphan*/  hevc_h_loop_filter_chroma; int /*<<< orphan*/  hevc_v_loop_filter_chroma; void**** put_hevc_qpel; void**** put_hevc_epel; int /*<<< orphan*/ * add_residual; void**** put_hevc_qpel_bi; void**** put_hevc_qpel_uni; void**** put_hevc_epel_bi; void**** put_hevc_epel_uni; int /*<<< orphan*/ * idct; int /*<<< orphan*/ * sao_edge_filter; } ;
typedef  TYPE_1__ HEVCDSPContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86_64 ; 
 int /*<<< orphan*/  EPEL_LINKS (void****,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ EXTERNAL_AVX (int) ; 
 scalar_t__ EXTERNAL_AVX2 (int) ; 
 scalar_t__ EXTERNAL_AVX2_FAST (int) ; 
 scalar_t__ EXTERNAL_MMXEXT (int) ; 
 scalar_t__ EXTERNAL_SSE2 (int) ; 
 scalar_t__ EXTERNAL_SSE4 (int) ; 
 scalar_t__ EXTERNAL_SSSE3 (int) ; 
 int /*<<< orphan*/  QPEL_LINKS (void****,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAO_BAND_INIT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAO_EDGE_INIT (int,int /*<<< orphan*/ ) ; 
 int av_get_cpu_flags () ; 
 int /*<<< orphan*/  avx ; 
 int /*<<< orphan*/  avx2 ; 
 int /*<<< orphan*/  epel_h ; 
 int /*<<< orphan*/  epel_hv ; 
 int /*<<< orphan*/  epel_v ; 
 int /*<<< orphan*/  ff_hevc_add_residual_16_10_avx2 ; 
 int /*<<< orphan*/  ff_hevc_add_residual_16_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_add_residual_16_8_avx ; 
 int /*<<< orphan*/  ff_hevc_add_residual_16_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_add_residual_32_10_avx2 ; 
 int /*<<< orphan*/  ff_hevc_add_residual_32_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_add_residual_32_8_avx ; 
 int /*<<< orphan*/  ff_hevc_add_residual_32_8_avx2 ; 
 int /*<<< orphan*/  ff_hevc_add_residual_32_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_add_residual_4_10_mmxext ; 
 int /*<<< orphan*/  ff_hevc_add_residual_4_8_mmxext ; 
 int /*<<< orphan*/  ff_hevc_add_residual_8_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_add_residual_8_8_avx ; 
 int /*<<< orphan*/  ff_hevc_add_residual_8_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_chroma_10_avx ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_chroma_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_chroma_12_avx ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_chroma_12_sse2 ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_chroma_8_avx ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_chroma_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_luma_10_avx ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_luma_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_luma_10_ssse3 ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_luma_12_avx ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_luma_12_sse2 ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_luma_12_ssse3 ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_luma_8_avx ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_luma_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_h_loop_filter_luma_8_ssse3 ; 
 int /*<<< orphan*/  ff_hevc_idct_16x16_10_avx ; 
 int /*<<< orphan*/  ff_hevc_idct_16x16_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_16x16_8_avx ; 
 int /*<<< orphan*/  ff_hevc_idct_16x16_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_16x16_dc_10_avx2 ; 
 int /*<<< orphan*/  ff_hevc_idct_16x16_dc_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_16x16_dc_12_avx2 ; 
 int /*<<< orphan*/  ff_hevc_idct_16x16_dc_12_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_16x16_dc_8_avx2 ; 
 int /*<<< orphan*/  ff_hevc_idct_16x16_dc_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_32x32_10_avx ; 
 int /*<<< orphan*/  ff_hevc_idct_32x32_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_32x32_8_avx ; 
 int /*<<< orphan*/  ff_hevc_idct_32x32_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_32x32_dc_10_avx2 ; 
 int /*<<< orphan*/  ff_hevc_idct_32x32_dc_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_32x32_dc_12_avx2 ; 
 int /*<<< orphan*/  ff_hevc_idct_32x32_dc_12_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_32x32_dc_8_avx2 ; 
 int /*<<< orphan*/  ff_hevc_idct_32x32_dc_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_4x4_10_avx ; 
 int /*<<< orphan*/  ff_hevc_idct_4x4_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_4x4_8_avx ; 
 int /*<<< orphan*/  ff_hevc_idct_4x4_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_4x4_dc_10_mmxext ; 
 int /*<<< orphan*/  ff_hevc_idct_4x4_dc_12_mmxext ; 
 int /*<<< orphan*/  ff_hevc_idct_4x4_dc_8_mmxext ; 
 int /*<<< orphan*/  ff_hevc_idct_8x8_10_avx ; 
 int /*<<< orphan*/  ff_hevc_idct_8x8_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_8x8_8_avx ; 
 int /*<<< orphan*/  ff_hevc_idct_8x8_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_8x8_dc_10_mmxext ; 
 int /*<<< orphan*/  ff_hevc_idct_8x8_dc_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_8x8_dc_12_mmxext ; 
 int /*<<< orphan*/  ff_hevc_idct_8x8_dc_12_sse2 ; 
 int /*<<< orphan*/  ff_hevc_idct_8x8_dc_8_mmxext ; 
 int /*<<< orphan*/  ff_hevc_idct_8x8_dc_8_sse2 ; 
 void* ff_hevc_put_hevc_bi_epel_h16_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_h24_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_h32_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_h32_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_h48_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_h48_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_h64_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_h64_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_hv16_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_hv24_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_hv32_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_hv32_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_hv48_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_hv48_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_hv64_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_hv64_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_v16_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_v24_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_v32_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_v32_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_v48_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_v48_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_v64_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_epel_v64_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_pel_pixels16_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_pel_pixels24_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_pel_pixels32_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_pel_pixels32_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_pel_pixels48_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_pel_pixels48_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_pel_pixels64_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_pel_pixels64_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_h16_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_h24_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_h32_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_h32_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_h48_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_h48_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_h64_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_h64_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_hv16_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_hv24_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_hv32_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_hv48_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_hv64_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_v16_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_v24_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_v32_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_v32_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_v48_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_v48_8_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_v64_10_avx2 ; 
 void* ff_hevc_put_hevc_bi_qpel_v64_8_avx2 ; 
 void* ff_hevc_put_hevc_epel_h16_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_h24_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_h32_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_h32_8_avx2 ; 
 void* ff_hevc_put_hevc_epel_h48_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_h48_8_avx2 ; 
 void* ff_hevc_put_hevc_epel_h64_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_h64_8_avx2 ; 
 void* ff_hevc_put_hevc_epel_hv16_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_hv24_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_hv32_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_hv32_8_avx2 ; 
 void* ff_hevc_put_hevc_epel_hv48_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_hv48_8_avx2 ; 
 void* ff_hevc_put_hevc_epel_hv64_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_hv64_8_avx2 ; 
 void* ff_hevc_put_hevc_epel_v16_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_v24_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_v32_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_v32_8_avx2 ; 
 void* ff_hevc_put_hevc_epel_v48_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_v48_8_avx2 ; 
 void* ff_hevc_put_hevc_epel_v64_10_avx2 ; 
 void* ff_hevc_put_hevc_epel_v64_8_avx2 ; 
 void* ff_hevc_put_hevc_pel_pixels16_10_avx2 ; 
 void* ff_hevc_put_hevc_pel_pixels24_10_avx2 ; 
 void* ff_hevc_put_hevc_pel_pixels32_10_avx2 ; 
 void* ff_hevc_put_hevc_pel_pixels32_8_avx2 ; 
 void* ff_hevc_put_hevc_pel_pixels48_10_avx2 ; 
 void* ff_hevc_put_hevc_pel_pixels48_8_avx2 ; 
 void* ff_hevc_put_hevc_pel_pixels64_10_avx2 ; 
 void* ff_hevc_put_hevc_pel_pixels64_8_avx2 ; 
 void* ff_hevc_put_hevc_qpel_h16_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_h24_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_h32_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_h32_8_avx2 ; 
 void* ff_hevc_put_hevc_qpel_h48_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_h48_8_avx2 ; 
 void* ff_hevc_put_hevc_qpel_h64_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_h64_8_avx2 ; 
 void* ff_hevc_put_hevc_qpel_hv16_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_hv24_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_hv32_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_hv48_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_hv64_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_v16_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_v24_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_v32_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_v32_8_avx2 ; 
 void* ff_hevc_put_hevc_qpel_v48_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_v48_8_avx2 ; 
 void* ff_hevc_put_hevc_qpel_v64_10_avx2 ; 
 void* ff_hevc_put_hevc_qpel_v64_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_h16_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_h24_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_h32_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_h32_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_h48_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_h48_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_h64_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_h64_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_hv16_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_hv24_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_hv32_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_hv32_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_hv48_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_hv48_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_hv64_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_hv64_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_v16_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_v24_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_v32_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_v32_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_v48_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_v48_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_v64_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_epel_v64_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_pel_pixels128_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_pel_pixels32_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_pel_pixels48_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_pel_pixels64_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_pel_pixels96_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_h16_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_h24_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_h32_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_h32_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_h48_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_h48_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_h64_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_h64_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_hv16_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_hv24_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_hv32_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_hv48_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_hv64_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_v16_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_v24_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_v32_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_v32_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_v48_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_v48_8_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_v64_10_avx2 ; 
 void* ff_hevc_put_hevc_uni_qpel_v64_8_avx2 ; 
 int /*<<< orphan*/  ff_hevc_sao_band_filter_16_8_avx2 ; 
 int /*<<< orphan*/  ff_hevc_sao_band_filter_8_10_avx2 ; 
 int /*<<< orphan*/  ff_hevc_sao_band_filter_8_12_avx2 ; 
 int /*<<< orphan*/  ff_hevc_sao_band_filter_8_8_avx2 ; 
 int /*<<< orphan*/  ff_hevc_sao_edge_filter_32_8_avx2 ; 
 int /*<<< orphan*/  ff_hevc_sao_edge_filter_48_8_avx2 ; 
 int /*<<< orphan*/  ff_hevc_sao_edge_filter_64_8_avx2 ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_chroma_10_avx ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_chroma_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_chroma_12_avx ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_chroma_12_sse2 ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_chroma_8_avx ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_chroma_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_luma_10_avx ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_luma_10_sse2 ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_luma_10_ssse3 ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_luma_12_avx ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_luma_12_sse2 ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_luma_12_ssse3 ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_luma_8_avx ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_luma_8_sse2 ; 
 int /*<<< orphan*/  ff_hevc_v_loop_filter_luma_8_ssse3 ; 
 int /*<<< orphan*/  pel_pixels ; 
 int /*<<< orphan*/  qpel_h ; 
 int /*<<< orphan*/  qpel_hv ; 
 int /*<<< orphan*/  qpel_v ; 
 int /*<<< orphan*/  sse2 ; 
 int /*<<< orphan*/  sse4 ; 
 int /*<<< orphan*/  ssse3 ; 

void ff_hevc_dsp_init_x86(HEVCDSPContext *c, const int bit_depth)
{
    int cpu_flags = av_get_cpu_flags();

    if (bit_depth == 8) {
        if (EXTERNAL_MMXEXT(cpu_flags)) {
            c->idct_dc[0] = ff_hevc_idct_4x4_dc_8_mmxext;
            c->idct_dc[1] = ff_hevc_idct_8x8_dc_8_mmxext;

            c->add_residual[0] = ff_hevc_add_residual_4_8_mmxext;
        }
        if (EXTERNAL_SSE2(cpu_flags)) {
            c->hevc_v_loop_filter_chroma = ff_hevc_v_loop_filter_chroma_8_sse2;
            c->hevc_h_loop_filter_chroma = ff_hevc_h_loop_filter_chroma_8_sse2;
            if (ARCH_X86_64) {
                c->hevc_v_loop_filter_luma = ff_hevc_v_loop_filter_luma_8_sse2;
                c->hevc_h_loop_filter_luma = ff_hevc_h_loop_filter_luma_8_sse2;

                c->idct[2] = ff_hevc_idct_16x16_8_sse2;
                c->idct[3] = ff_hevc_idct_32x32_8_sse2;
            }
            SAO_BAND_INIT(8, sse2);

            c->idct_dc[1] = ff_hevc_idct_8x8_dc_8_sse2;
            c->idct_dc[2] = ff_hevc_idct_16x16_dc_8_sse2;
            c->idct_dc[3] = ff_hevc_idct_32x32_dc_8_sse2;

            c->idct[0]    = ff_hevc_idct_4x4_8_sse2;
            c->idct[1]    = ff_hevc_idct_8x8_8_sse2;

            c->add_residual[1] = ff_hevc_add_residual_8_8_sse2;
            c->add_residual[2] = ff_hevc_add_residual_16_8_sse2;
            c->add_residual[3] = ff_hevc_add_residual_32_8_sse2;
        }
        if (EXTERNAL_SSSE3(cpu_flags)) {
            if(ARCH_X86_64) {
                c->hevc_v_loop_filter_luma = ff_hevc_v_loop_filter_luma_8_ssse3;
                c->hevc_h_loop_filter_luma = ff_hevc_h_loop_filter_luma_8_ssse3;
            }
            SAO_EDGE_INIT(8, ssse3);
        }
        if (EXTERNAL_SSE4(cpu_flags) && ARCH_X86_64) {

            EPEL_LINKS(c->put_hevc_epel, 0, 0, pel_pixels,  8, sse4);
            EPEL_LINKS(c->put_hevc_epel, 0, 1, epel_h,      8, sse4);
            EPEL_LINKS(c->put_hevc_epel, 1, 0, epel_v,      8, sse4);
            EPEL_LINKS(c->put_hevc_epel, 1, 1, epel_hv,     8, sse4);

            QPEL_LINKS(c->put_hevc_qpel, 0, 0, pel_pixels, 8, sse4);
            QPEL_LINKS(c->put_hevc_qpel, 0, 1, qpel_h,     8, sse4);
            QPEL_LINKS(c->put_hevc_qpel, 1, 0, qpel_v,     8, sse4);
            QPEL_LINKS(c->put_hevc_qpel, 1, 1, qpel_hv,    8, sse4);
        }
        if (EXTERNAL_AVX(cpu_flags)) {
            c->hevc_v_loop_filter_chroma = ff_hevc_v_loop_filter_chroma_8_avx;
            c->hevc_h_loop_filter_chroma = ff_hevc_h_loop_filter_chroma_8_avx;
            if (ARCH_X86_64) {
                c->hevc_v_loop_filter_luma = ff_hevc_v_loop_filter_luma_8_avx;
                c->hevc_h_loop_filter_luma = ff_hevc_h_loop_filter_luma_8_avx;

                c->idct[2] = ff_hevc_idct_16x16_8_avx;
                c->idct[3] = ff_hevc_idct_32x32_8_avx;
            }
            SAO_BAND_INIT(8, avx);

            c->idct[0] = ff_hevc_idct_4x4_8_avx;
            c->idct[1] = ff_hevc_idct_8x8_8_avx;

            c->add_residual[1] = ff_hevc_add_residual_8_8_avx;
            c->add_residual[2] = ff_hevc_add_residual_16_8_avx;
            c->add_residual[3] = ff_hevc_add_residual_32_8_avx;
        }
        if (EXTERNAL_AVX2(cpu_flags)) {
            c->sao_band_filter[0] = ff_hevc_sao_band_filter_8_8_avx2;
            c->sao_band_filter[1] = ff_hevc_sao_band_filter_16_8_avx2;
        }
        if (EXTERNAL_AVX2_FAST(cpu_flags)) {
            c->idct_dc[2] = ff_hevc_idct_16x16_dc_8_avx2;
            c->idct_dc[3] = ff_hevc_idct_32x32_dc_8_avx2;
            if (ARCH_X86_64) {
                c->put_hevc_epel[7][0][0] = ff_hevc_put_hevc_pel_pixels32_8_avx2;
                c->put_hevc_epel[8][0][0] = ff_hevc_put_hevc_pel_pixels48_8_avx2;
                c->put_hevc_epel[9][0][0] = ff_hevc_put_hevc_pel_pixels64_8_avx2;

                c->put_hevc_qpel[7][0][0] = ff_hevc_put_hevc_pel_pixels32_8_avx2;
                c->put_hevc_qpel[8][0][0] = ff_hevc_put_hevc_pel_pixels48_8_avx2;
                c->put_hevc_qpel[9][0][0] = ff_hevc_put_hevc_pel_pixels64_8_avx2;

                c->put_hevc_epel_uni[7][0][0] = ff_hevc_put_hevc_uni_pel_pixels32_8_avx2;
                c->put_hevc_epel_uni[8][0][0] = ff_hevc_put_hevc_uni_pel_pixels48_8_avx2;
                c->put_hevc_epel_uni[9][0][0] = ff_hevc_put_hevc_uni_pel_pixels64_8_avx2;

                c->put_hevc_qpel_uni[7][0][0] = ff_hevc_put_hevc_uni_pel_pixels32_8_avx2;
                c->put_hevc_qpel_uni[8][0][0] = ff_hevc_put_hevc_uni_pel_pixels48_8_avx2;
                c->put_hevc_qpel_uni[9][0][0] = ff_hevc_put_hevc_uni_pel_pixels64_8_avx2;

                c->put_hevc_qpel_bi[7][0][0] = ff_hevc_put_hevc_bi_pel_pixels32_8_avx2;
                c->put_hevc_qpel_bi[8][0][0] = ff_hevc_put_hevc_bi_pel_pixels48_8_avx2;
                c->put_hevc_qpel_bi[9][0][0] = ff_hevc_put_hevc_bi_pel_pixels64_8_avx2;

                c->put_hevc_epel_bi[7][0][0] = ff_hevc_put_hevc_bi_pel_pixels32_8_avx2;
                c->put_hevc_epel_bi[8][0][0] = ff_hevc_put_hevc_bi_pel_pixels48_8_avx2;
                c->put_hevc_epel_bi[9][0][0] = ff_hevc_put_hevc_bi_pel_pixels64_8_avx2;

                c->put_hevc_epel[7][0][1] = ff_hevc_put_hevc_epel_h32_8_avx2;
                c->put_hevc_epel[8][0][1] = ff_hevc_put_hevc_epel_h48_8_avx2;
                c->put_hevc_epel[9][0][1] = ff_hevc_put_hevc_epel_h64_8_avx2;

                c->put_hevc_epel_uni[7][0][1] = ff_hevc_put_hevc_uni_epel_h32_8_avx2;
                c->put_hevc_epel_uni[8][0][1] = ff_hevc_put_hevc_uni_epel_h48_8_avx2;
                c->put_hevc_epel_uni[9][0][1] = ff_hevc_put_hevc_uni_epel_h64_8_avx2;

                c->put_hevc_epel_bi[7][0][1] = ff_hevc_put_hevc_bi_epel_h32_8_avx2;
                c->put_hevc_epel_bi[8][0][1] = ff_hevc_put_hevc_bi_epel_h48_8_avx2;
                c->put_hevc_epel_bi[9][0][1] = ff_hevc_put_hevc_bi_epel_h64_8_avx2;

                c->put_hevc_epel[7][1][0] = ff_hevc_put_hevc_epel_v32_8_avx2;
                c->put_hevc_epel[8][1][0] = ff_hevc_put_hevc_epel_v48_8_avx2;
                c->put_hevc_epel[9][1][0] = ff_hevc_put_hevc_epel_v64_8_avx2;

                c->put_hevc_epel_uni[7][1][0] = ff_hevc_put_hevc_uni_epel_v32_8_avx2;
                c->put_hevc_epel_uni[8][1][0] = ff_hevc_put_hevc_uni_epel_v48_8_avx2;
                c->put_hevc_epel_uni[9][1][0] = ff_hevc_put_hevc_uni_epel_v64_8_avx2;

                c->put_hevc_epel_bi[7][1][0] = ff_hevc_put_hevc_bi_epel_v32_8_avx2;
                c->put_hevc_epel_bi[8][1][0] = ff_hevc_put_hevc_bi_epel_v48_8_avx2;
                c->put_hevc_epel_bi[9][1][0] = ff_hevc_put_hevc_bi_epel_v64_8_avx2;

                c->put_hevc_epel[7][1][1] = ff_hevc_put_hevc_epel_hv32_8_avx2;
                c->put_hevc_epel[8][1][1] = ff_hevc_put_hevc_epel_hv48_8_avx2;
                c->put_hevc_epel[9][1][1] = ff_hevc_put_hevc_epel_hv64_8_avx2;

                c->put_hevc_epel_uni[7][1][1] = ff_hevc_put_hevc_uni_epel_hv32_8_avx2;
                c->put_hevc_epel_uni[8][1][1] = ff_hevc_put_hevc_uni_epel_hv48_8_avx2;
                c->put_hevc_epel_uni[9][1][1] = ff_hevc_put_hevc_uni_epel_hv64_8_avx2;

                c->put_hevc_epel_bi[7][1][1] = ff_hevc_put_hevc_bi_epel_hv32_8_avx2;
                c->put_hevc_epel_bi[8][1][1] = ff_hevc_put_hevc_bi_epel_hv48_8_avx2;
                c->put_hevc_epel_bi[9][1][1] = ff_hevc_put_hevc_bi_epel_hv64_8_avx2;

                c->put_hevc_qpel[7][0][1] = ff_hevc_put_hevc_qpel_h32_8_avx2;
                c->put_hevc_qpel[8][0][1] = ff_hevc_put_hevc_qpel_h48_8_avx2;
                c->put_hevc_qpel[9][0][1] = ff_hevc_put_hevc_qpel_h64_8_avx2;

                c->put_hevc_qpel[7][1][0] = ff_hevc_put_hevc_qpel_v32_8_avx2;
                c->put_hevc_qpel[8][1][0] = ff_hevc_put_hevc_qpel_v48_8_avx2;
                c->put_hevc_qpel[9][1][0] = ff_hevc_put_hevc_qpel_v64_8_avx2;

                c->put_hevc_qpel_uni[7][0][1] = ff_hevc_put_hevc_uni_qpel_h32_8_avx2;
                c->put_hevc_qpel_uni[8][0][1] = ff_hevc_put_hevc_uni_qpel_h48_8_avx2;
                c->put_hevc_qpel_uni[9][0][1] = ff_hevc_put_hevc_uni_qpel_h64_8_avx2;

                c->put_hevc_qpel_uni[7][1][0] = ff_hevc_put_hevc_uni_qpel_v32_8_avx2;
                c->put_hevc_qpel_uni[8][1][0] = ff_hevc_put_hevc_uni_qpel_v48_8_avx2;
                c->put_hevc_qpel_uni[9][1][0] = ff_hevc_put_hevc_uni_qpel_v64_8_avx2;

                c->put_hevc_qpel_bi[7][0][1] = ff_hevc_put_hevc_bi_qpel_h32_8_avx2;
                c->put_hevc_qpel_bi[8][0][1] = ff_hevc_put_hevc_bi_qpel_h48_8_avx2;
                c->put_hevc_qpel_bi[9][0][1] = ff_hevc_put_hevc_bi_qpel_h64_8_avx2;

                c->put_hevc_qpel_bi[7][1][0] = ff_hevc_put_hevc_bi_qpel_v32_8_avx2;
                c->put_hevc_qpel_bi[8][1][0] = ff_hevc_put_hevc_bi_qpel_v48_8_avx2;
                c->put_hevc_qpel_bi[9][1][0] = ff_hevc_put_hevc_bi_qpel_v64_8_avx2;
            }
            SAO_BAND_INIT(8, avx2);

            c->sao_edge_filter[2] = ff_hevc_sao_edge_filter_32_8_avx2;
            c->sao_edge_filter[3] = ff_hevc_sao_edge_filter_48_8_avx2;
            c->sao_edge_filter[4] = ff_hevc_sao_edge_filter_64_8_avx2;

            c->add_residual[3] = ff_hevc_add_residual_32_8_avx2;
        }
    } else if (bit_depth == 10) {
        if (EXTERNAL_MMXEXT(cpu_flags)) {
            c->add_residual[0] = ff_hevc_add_residual_4_10_mmxext;
            c->idct_dc[0] = ff_hevc_idct_4x4_dc_10_mmxext;
            c->idct_dc[1] = ff_hevc_idct_8x8_dc_10_mmxext;
        }
        if (EXTERNAL_SSE2(cpu_flags)) {
            c->hevc_v_loop_filter_chroma = ff_hevc_v_loop_filter_chroma_10_sse2;
            c->hevc_h_loop_filter_chroma = ff_hevc_h_loop_filter_chroma_10_sse2;
            if (ARCH_X86_64) {
                c->hevc_v_loop_filter_luma = ff_hevc_v_loop_filter_luma_10_sse2;
                c->hevc_h_loop_filter_luma = ff_hevc_h_loop_filter_luma_10_sse2;

                c->idct[2] = ff_hevc_idct_16x16_10_sse2;
                c->idct[3] = ff_hevc_idct_32x32_10_sse2;
            }
            SAO_BAND_INIT(10, sse2);
            SAO_EDGE_INIT(10, sse2);

            c->idct_dc[1] = ff_hevc_idct_8x8_dc_10_sse2;
            c->idct_dc[2] = ff_hevc_idct_16x16_dc_10_sse2;
            c->idct_dc[3] = ff_hevc_idct_32x32_dc_10_sse2;

            c->idct[0]    = ff_hevc_idct_4x4_10_sse2;
            c->idct[1]    = ff_hevc_idct_8x8_10_sse2;

            c->add_residual[1] = ff_hevc_add_residual_8_10_sse2;
            c->add_residual[2] = ff_hevc_add_residual_16_10_sse2;
            c->add_residual[3] = ff_hevc_add_residual_32_10_sse2;
        }
        if (EXTERNAL_SSSE3(cpu_flags) && ARCH_X86_64) {
            c->hevc_v_loop_filter_luma = ff_hevc_v_loop_filter_luma_10_ssse3;
            c->hevc_h_loop_filter_luma = ff_hevc_h_loop_filter_luma_10_ssse3;
        }
        if (EXTERNAL_SSE4(cpu_flags) && ARCH_X86_64) {
            EPEL_LINKS(c->put_hevc_epel, 0, 0, pel_pixels, 10, sse4);
            EPEL_LINKS(c->put_hevc_epel, 0, 1, epel_h,     10, sse4);
            EPEL_LINKS(c->put_hevc_epel, 1, 0, epel_v,     10, sse4);
            EPEL_LINKS(c->put_hevc_epel, 1, 1, epel_hv,    10, sse4);

            QPEL_LINKS(c->put_hevc_qpel, 0, 0, pel_pixels, 10, sse4);
            QPEL_LINKS(c->put_hevc_qpel, 0, 1, qpel_h,     10, sse4);
            QPEL_LINKS(c->put_hevc_qpel, 1, 0, qpel_v,     10, sse4);
            QPEL_LINKS(c->put_hevc_qpel, 1, 1, qpel_hv,    10, sse4);
        }
        if (EXTERNAL_AVX(cpu_flags)) {
            c->hevc_v_loop_filter_chroma = ff_hevc_v_loop_filter_chroma_10_avx;
            c->hevc_h_loop_filter_chroma = ff_hevc_h_loop_filter_chroma_10_avx;
            if (ARCH_X86_64) {
                c->hevc_v_loop_filter_luma = ff_hevc_v_loop_filter_luma_10_avx;
                c->hevc_h_loop_filter_luma = ff_hevc_h_loop_filter_luma_10_avx;

                c->idct[2] = ff_hevc_idct_16x16_10_avx;
                c->idct[3] = ff_hevc_idct_32x32_10_avx;
            }

            c->idct[0] = ff_hevc_idct_4x4_10_avx;
            c->idct[1] = ff_hevc_idct_8x8_10_avx;

            SAO_BAND_INIT(10, avx);
        }
        if (EXTERNAL_AVX2(cpu_flags)) {
            c->sao_band_filter[0] = ff_hevc_sao_band_filter_8_10_avx2;
        }
        if (EXTERNAL_AVX2_FAST(cpu_flags)) {
            c->idct_dc[2] = ff_hevc_idct_16x16_dc_10_avx2;
            c->idct_dc[3] = ff_hevc_idct_32x32_dc_10_avx2;
            if (ARCH_X86_64) {
                c->put_hevc_epel[5][0][0] = ff_hevc_put_hevc_pel_pixels16_10_avx2;
                c->put_hevc_epel[6][0][0] = ff_hevc_put_hevc_pel_pixels24_10_avx2;
                c->put_hevc_epel[7][0][0] = ff_hevc_put_hevc_pel_pixels32_10_avx2;
                c->put_hevc_epel[8][0][0] = ff_hevc_put_hevc_pel_pixels48_10_avx2;
                c->put_hevc_epel[9][0][0] = ff_hevc_put_hevc_pel_pixels64_10_avx2;

                c->put_hevc_qpel[5][0][0] = ff_hevc_put_hevc_pel_pixels16_10_avx2;
                c->put_hevc_qpel[6][0][0] = ff_hevc_put_hevc_pel_pixels24_10_avx2;
                c->put_hevc_qpel[7][0][0] = ff_hevc_put_hevc_pel_pixels32_10_avx2;
                c->put_hevc_qpel[8][0][0] = ff_hevc_put_hevc_pel_pixels48_10_avx2;
                c->put_hevc_qpel[9][0][0] = ff_hevc_put_hevc_pel_pixels64_10_avx2;

                c->put_hevc_epel_uni[5][0][0] = ff_hevc_put_hevc_uni_pel_pixels32_8_avx2;
                c->put_hevc_epel_uni[6][0][0] = ff_hevc_put_hevc_uni_pel_pixels48_8_avx2;
                c->put_hevc_epel_uni[7][0][0] = ff_hevc_put_hevc_uni_pel_pixels64_8_avx2;
                c->put_hevc_epel_uni[8][0][0] = ff_hevc_put_hevc_uni_pel_pixels96_8_avx2;
                c->put_hevc_epel_uni[9][0][0] = ff_hevc_put_hevc_uni_pel_pixels128_8_avx2;

                c->put_hevc_qpel_uni[5][0][0] = ff_hevc_put_hevc_uni_pel_pixels32_8_avx2;
                c->put_hevc_qpel_uni[6][0][0] = ff_hevc_put_hevc_uni_pel_pixels48_8_avx2;
                c->put_hevc_qpel_uni[7][0][0] = ff_hevc_put_hevc_uni_pel_pixels64_8_avx2;
                c->put_hevc_qpel_uni[8][0][0] = ff_hevc_put_hevc_uni_pel_pixels96_8_avx2;
                c->put_hevc_qpel_uni[9][0][0] = ff_hevc_put_hevc_uni_pel_pixels128_8_avx2;

                c->put_hevc_epel_bi[5][0][0] = ff_hevc_put_hevc_bi_pel_pixels16_10_avx2;
                c->put_hevc_epel_bi[6][0][0] = ff_hevc_put_hevc_bi_pel_pixels24_10_avx2;
                c->put_hevc_epel_bi[7][0][0] = ff_hevc_put_hevc_bi_pel_pixels32_10_avx2;
                c->put_hevc_epel_bi[8][0][0] = ff_hevc_put_hevc_bi_pel_pixels48_10_avx2;
                c->put_hevc_epel_bi[9][0][0] = ff_hevc_put_hevc_bi_pel_pixels64_10_avx2;
                c->put_hevc_qpel_bi[5][0][0] = ff_hevc_put_hevc_bi_pel_pixels16_10_avx2;
                c->put_hevc_qpel_bi[6][0][0] = ff_hevc_put_hevc_bi_pel_pixels24_10_avx2;
                c->put_hevc_qpel_bi[7][0][0] = ff_hevc_put_hevc_bi_pel_pixels32_10_avx2;
                c->put_hevc_qpel_bi[8][0][0] = ff_hevc_put_hevc_bi_pel_pixels48_10_avx2;
                c->put_hevc_qpel_bi[9][0][0] = ff_hevc_put_hevc_bi_pel_pixels64_10_avx2;

                c->put_hevc_epel[5][0][1] = ff_hevc_put_hevc_epel_h16_10_avx2;
                c->put_hevc_epel[6][0][1] = ff_hevc_put_hevc_epel_h24_10_avx2;
                c->put_hevc_epel[7][0][1] = ff_hevc_put_hevc_epel_h32_10_avx2;
                c->put_hevc_epel[8][0][1] = ff_hevc_put_hevc_epel_h48_10_avx2;
                c->put_hevc_epel[9][0][1] = ff_hevc_put_hevc_epel_h64_10_avx2;

                c->put_hevc_epel_uni[5][0][1] = ff_hevc_put_hevc_uni_epel_h16_10_avx2;
                c->put_hevc_epel_uni[6][0][1] = ff_hevc_put_hevc_uni_epel_h24_10_avx2;
                c->put_hevc_epel_uni[7][0][1] = ff_hevc_put_hevc_uni_epel_h32_10_avx2;
                c->put_hevc_epel_uni[8][0][1] = ff_hevc_put_hevc_uni_epel_h48_10_avx2;
                c->put_hevc_epel_uni[9][0][1] = ff_hevc_put_hevc_uni_epel_h64_10_avx2;

                c->put_hevc_epel_bi[5][0][1] = ff_hevc_put_hevc_bi_epel_h16_10_avx2;
                c->put_hevc_epel_bi[6][0][1] = ff_hevc_put_hevc_bi_epel_h24_10_avx2;
                c->put_hevc_epel_bi[7][0][1] = ff_hevc_put_hevc_bi_epel_h32_10_avx2;
                c->put_hevc_epel_bi[8][0][1] = ff_hevc_put_hevc_bi_epel_h48_10_avx2;
                c->put_hevc_epel_bi[9][0][1] = ff_hevc_put_hevc_bi_epel_h64_10_avx2;

                c->put_hevc_epel[5][1][0] = ff_hevc_put_hevc_epel_v16_10_avx2;
                c->put_hevc_epel[6][1][0] = ff_hevc_put_hevc_epel_v24_10_avx2;
                c->put_hevc_epel[7][1][0] = ff_hevc_put_hevc_epel_v32_10_avx2;
                c->put_hevc_epel[8][1][0] = ff_hevc_put_hevc_epel_v48_10_avx2;
                c->put_hevc_epel[9][1][0] = ff_hevc_put_hevc_epel_v64_10_avx2;

                c->put_hevc_epel_uni[5][1][0] = ff_hevc_put_hevc_uni_epel_v16_10_avx2;
                c->put_hevc_epel_uni[6][1][0] = ff_hevc_put_hevc_uni_epel_v24_10_avx2;
                c->put_hevc_epel_uni[7][1][0] = ff_hevc_put_hevc_uni_epel_v32_10_avx2;
                c->put_hevc_epel_uni[8][1][0] = ff_hevc_put_hevc_uni_epel_v48_10_avx2;
                c->put_hevc_epel_uni[9][1][0] = ff_hevc_put_hevc_uni_epel_v64_10_avx2;

                c->put_hevc_epel_bi[5][1][0] = ff_hevc_put_hevc_bi_epel_v16_10_avx2;
                c->put_hevc_epel_bi[6][1][0] = ff_hevc_put_hevc_bi_epel_v24_10_avx2;
                c->put_hevc_epel_bi[7][1][0] = ff_hevc_put_hevc_bi_epel_v32_10_avx2;
                c->put_hevc_epel_bi[8][1][0] = ff_hevc_put_hevc_bi_epel_v48_10_avx2;
                c->put_hevc_epel_bi[9][1][0] = ff_hevc_put_hevc_bi_epel_v64_10_avx2;

                c->put_hevc_epel[5][1][1] = ff_hevc_put_hevc_epel_hv16_10_avx2;
                c->put_hevc_epel[6][1][1] = ff_hevc_put_hevc_epel_hv24_10_avx2;
                c->put_hevc_epel[7][1][1] = ff_hevc_put_hevc_epel_hv32_10_avx2;
                c->put_hevc_epel[8][1][1] = ff_hevc_put_hevc_epel_hv48_10_avx2;
                c->put_hevc_epel[9][1][1] = ff_hevc_put_hevc_epel_hv64_10_avx2;

                c->put_hevc_epel_uni[5][1][1] = ff_hevc_put_hevc_uni_epel_hv16_10_avx2;
                c->put_hevc_epel_uni[6][1][1] = ff_hevc_put_hevc_uni_epel_hv24_10_avx2;
                c->put_hevc_epel_uni[7][1][1] = ff_hevc_put_hevc_uni_epel_hv32_10_avx2;
                c->put_hevc_epel_uni[8][1][1] = ff_hevc_put_hevc_uni_epel_hv48_10_avx2;
                c->put_hevc_epel_uni[9][1][1] = ff_hevc_put_hevc_uni_epel_hv64_10_avx2;

                c->put_hevc_epel_bi[5][1][1] = ff_hevc_put_hevc_bi_epel_hv16_10_avx2;
                c->put_hevc_epel_bi[6][1][1] = ff_hevc_put_hevc_bi_epel_hv24_10_avx2;
                c->put_hevc_epel_bi[7][1][1] = ff_hevc_put_hevc_bi_epel_hv32_10_avx2;
                c->put_hevc_epel_bi[8][1][1] = ff_hevc_put_hevc_bi_epel_hv48_10_avx2;
                c->put_hevc_epel_bi[9][1][1] = ff_hevc_put_hevc_bi_epel_hv64_10_avx2;

                c->put_hevc_qpel[5][0][1] = ff_hevc_put_hevc_qpel_h16_10_avx2;
                c->put_hevc_qpel[6][0][1] = ff_hevc_put_hevc_qpel_h24_10_avx2;
                c->put_hevc_qpel[7][0][1] = ff_hevc_put_hevc_qpel_h32_10_avx2;
                c->put_hevc_qpel[8][0][1] = ff_hevc_put_hevc_qpel_h48_10_avx2;
                c->put_hevc_qpel[9][0][1] = ff_hevc_put_hevc_qpel_h64_10_avx2;

                c->put_hevc_qpel_uni[5][0][1] = ff_hevc_put_hevc_uni_qpel_h16_10_avx2;
                c->put_hevc_qpel_uni[6][0][1] = ff_hevc_put_hevc_uni_qpel_h24_10_avx2;
                c->put_hevc_qpel_uni[7][0][1] = ff_hevc_put_hevc_uni_qpel_h32_10_avx2;
                c->put_hevc_qpel_uni[8][0][1] = ff_hevc_put_hevc_uni_qpel_h48_10_avx2;
                c->put_hevc_qpel_uni[9][0][1] = ff_hevc_put_hevc_uni_qpel_h64_10_avx2;

                c->put_hevc_qpel_bi[5][0][1] = ff_hevc_put_hevc_bi_qpel_h16_10_avx2;
                c->put_hevc_qpel_bi[6][0][1] = ff_hevc_put_hevc_bi_qpel_h24_10_avx2;
                c->put_hevc_qpel_bi[7][0][1] = ff_hevc_put_hevc_bi_qpel_h32_10_avx2;
                c->put_hevc_qpel_bi[8][0][1] = ff_hevc_put_hevc_bi_qpel_h48_10_avx2;
                c->put_hevc_qpel_bi[9][0][1] = ff_hevc_put_hevc_bi_qpel_h64_10_avx2;

                c->put_hevc_qpel[5][1][0] = ff_hevc_put_hevc_qpel_v16_10_avx2;
                c->put_hevc_qpel[6][1][0] = ff_hevc_put_hevc_qpel_v24_10_avx2;
                c->put_hevc_qpel[7][1][0] = ff_hevc_put_hevc_qpel_v32_10_avx2;
                c->put_hevc_qpel[8][1][0] = ff_hevc_put_hevc_qpel_v48_10_avx2;
                c->put_hevc_qpel[9][1][0] = ff_hevc_put_hevc_qpel_v64_10_avx2;

                c->put_hevc_qpel_uni[5][1][0] = ff_hevc_put_hevc_uni_qpel_v16_10_avx2;
                c->put_hevc_qpel_uni[6][1][0] = ff_hevc_put_hevc_uni_qpel_v24_10_avx2;
                c->put_hevc_qpel_uni[7][1][0] = ff_hevc_put_hevc_uni_qpel_v32_10_avx2;
                c->put_hevc_qpel_uni[8][1][0] = ff_hevc_put_hevc_uni_qpel_v48_10_avx2;
                c->put_hevc_qpel_uni[9][1][0] = ff_hevc_put_hevc_uni_qpel_v64_10_avx2;

                c->put_hevc_qpel_bi[5][1][0] = ff_hevc_put_hevc_bi_qpel_v16_10_avx2;
                c->put_hevc_qpel_bi[6][1][0] = ff_hevc_put_hevc_bi_qpel_v24_10_avx2;
                c->put_hevc_qpel_bi[7][1][0] = ff_hevc_put_hevc_bi_qpel_v32_10_avx2;
                c->put_hevc_qpel_bi[8][1][0] = ff_hevc_put_hevc_bi_qpel_v48_10_avx2;
                c->put_hevc_qpel_bi[9][1][0] = ff_hevc_put_hevc_bi_qpel_v64_10_avx2;

                c->put_hevc_qpel[5][1][1] = ff_hevc_put_hevc_qpel_hv16_10_avx2;
                c->put_hevc_qpel[6][1][1] = ff_hevc_put_hevc_qpel_hv24_10_avx2;
                c->put_hevc_qpel[7][1][1] = ff_hevc_put_hevc_qpel_hv32_10_avx2;
                c->put_hevc_qpel[8][1][1] = ff_hevc_put_hevc_qpel_hv48_10_avx2;
                c->put_hevc_qpel[9][1][1] = ff_hevc_put_hevc_qpel_hv64_10_avx2;

                c->put_hevc_qpel_uni[5][1][1] = ff_hevc_put_hevc_uni_qpel_hv16_10_avx2;
                c->put_hevc_qpel_uni[6][1][1] = ff_hevc_put_hevc_uni_qpel_hv24_10_avx2;
                c->put_hevc_qpel_uni[7][1][1] = ff_hevc_put_hevc_uni_qpel_hv32_10_avx2;
                c->put_hevc_qpel_uni[8][1][1] = ff_hevc_put_hevc_uni_qpel_hv48_10_avx2;
                c->put_hevc_qpel_uni[9][1][1] = ff_hevc_put_hevc_uni_qpel_hv64_10_avx2;

                c->put_hevc_qpel_bi[5][1][1] = ff_hevc_put_hevc_bi_qpel_hv16_10_avx2;
                c->put_hevc_qpel_bi[6][1][1] = ff_hevc_put_hevc_bi_qpel_hv24_10_avx2;
                c->put_hevc_qpel_bi[7][1][1] = ff_hevc_put_hevc_bi_qpel_hv32_10_avx2;
                c->put_hevc_qpel_bi[8][1][1] = ff_hevc_put_hevc_bi_qpel_hv48_10_avx2;
                c->put_hevc_qpel_bi[9][1][1] = ff_hevc_put_hevc_bi_qpel_hv64_10_avx2;
            }
            SAO_BAND_INIT(10, avx2);
            SAO_EDGE_INIT(10, avx2);

            c->add_residual[2] = ff_hevc_add_residual_16_10_avx2;
            c->add_residual[3] = ff_hevc_add_residual_32_10_avx2;
        }
    } else if (bit_depth == 12) {
        if (EXTERNAL_MMXEXT(cpu_flags)) {
            c->idct_dc[0] = ff_hevc_idct_4x4_dc_12_mmxext;
            c->idct_dc[1] = ff_hevc_idct_8x8_dc_12_mmxext;
        }
        if (EXTERNAL_SSE2(cpu_flags)) {
            c->hevc_v_loop_filter_chroma = ff_hevc_v_loop_filter_chroma_12_sse2;
            c->hevc_h_loop_filter_chroma = ff_hevc_h_loop_filter_chroma_12_sse2;
            if (ARCH_X86_64) {
                c->hevc_v_loop_filter_luma = ff_hevc_v_loop_filter_luma_12_sse2;
                c->hevc_h_loop_filter_luma = ff_hevc_h_loop_filter_luma_12_sse2;
            }
            SAO_BAND_INIT(12, sse2);
            SAO_EDGE_INIT(12, sse2);

            c->idct_dc[1] = ff_hevc_idct_8x8_dc_12_sse2;
            c->idct_dc[2] = ff_hevc_idct_16x16_dc_12_sse2;
            c->idct_dc[3] = ff_hevc_idct_32x32_dc_12_sse2;
        }
        if (EXTERNAL_SSSE3(cpu_flags) && ARCH_X86_64) {
            c->hevc_v_loop_filter_luma = ff_hevc_v_loop_filter_luma_12_ssse3;
            c->hevc_h_loop_filter_luma = ff_hevc_h_loop_filter_luma_12_ssse3;
        }
        if (EXTERNAL_SSE4(cpu_flags) && ARCH_X86_64) {
            EPEL_LINKS(c->put_hevc_epel, 0, 0, pel_pixels, 12, sse4);
            EPEL_LINKS(c->put_hevc_epel, 0, 1, epel_h,     12, sse4);
            EPEL_LINKS(c->put_hevc_epel, 1, 0, epel_v,     12, sse4);
            EPEL_LINKS(c->put_hevc_epel, 1, 1, epel_hv,    12, sse4);

            QPEL_LINKS(c->put_hevc_qpel, 0, 0, pel_pixels, 12, sse4);
            QPEL_LINKS(c->put_hevc_qpel, 0, 1, qpel_h,     12, sse4);
            QPEL_LINKS(c->put_hevc_qpel, 1, 0, qpel_v,     12, sse4);
            QPEL_LINKS(c->put_hevc_qpel, 1, 1, qpel_hv,    12, sse4);
        }
        if (EXTERNAL_AVX(cpu_flags)) {
            c->hevc_v_loop_filter_chroma = ff_hevc_v_loop_filter_chroma_12_avx;
            c->hevc_h_loop_filter_chroma = ff_hevc_h_loop_filter_chroma_12_avx;
            if (ARCH_X86_64) {
                c->hevc_v_loop_filter_luma = ff_hevc_v_loop_filter_luma_12_avx;
                c->hevc_h_loop_filter_luma = ff_hevc_h_loop_filter_luma_12_avx;
            }
            SAO_BAND_INIT(12, avx);
        }
        if (EXTERNAL_AVX2(cpu_flags)) {
            c->sao_band_filter[0] = ff_hevc_sao_band_filter_8_12_avx2;
        }
        if (EXTERNAL_AVX2_FAST(cpu_flags)) {
            c->idct_dc[2] = ff_hevc_idct_16x16_dc_12_avx2;
            c->idct_dc[3] = ff_hevc_idct_32x32_dc_12_avx2;

            SAO_BAND_INIT(12, avx2);
            SAO_EDGE_INIT(12, avx2);
        }
    }
}