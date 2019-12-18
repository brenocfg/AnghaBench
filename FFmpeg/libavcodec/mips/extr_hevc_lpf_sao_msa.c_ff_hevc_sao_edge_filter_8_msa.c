#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int MAX_PB_SIZE ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_0degree_16multiple_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_0degree_4width_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_0degree_8width_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_135degree_16multiple_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_135degree_4width_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_135degree_8width_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_45degree_16multiple_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_45degree_4width_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_45degree_8width_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_90degree_16multiple_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_90degree_4width_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hevc_sao_edge_filter_90degree_8width_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

void ff_hevc_sao_edge_filter_8_msa(uint8_t *dst, uint8_t *src,
                                   ptrdiff_t stride_dst,
                                   int16_t *sao_offset_val,
                                   int eo, int width, int height)
{
    ptrdiff_t stride_src = (2 * MAX_PB_SIZE + AV_INPUT_BUFFER_PADDING_SIZE) / sizeof(uint8_t);

    switch (eo) {
    case 0:
        if (width >> 4) {
            hevc_sao_edge_filter_0degree_16multiple_msa(dst, stride_dst,
                                                        src, stride_src,
                                                        sao_offset_val,
                                                        width - (width % 16),
                                                        height);
            dst += width - (width % 16);
            src += width - (width % 16);
            width %= 16;
        }

        if (width >> 3) {
            hevc_sao_edge_filter_0degree_8width_msa(dst, stride_dst,
                                                    src, stride_src,
                                                    sao_offset_val, height);
            dst += 8;
            src += 8;
            width %= 8;
        }

        if (width) {
            hevc_sao_edge_filter_0degree_4width_msa(dst, stride_dst,
                                                    src, stride_src,
                                                    sao_offset_val, height);
        }
        break;

    case 1:
        if (width >> 4) {
            hevc_sao_edge_filter_90degree_16multiple_msa(dst, stride_dst,
                                                         src, stride_src,
                                                         sao_offset_val,
                                                         width - (width % 16),
                                                         height);
            dst += width - (width % 16);
            src += width - (width % 16);
            width %= 16;
        }

        if (width >> 3) {
            hevc_sao_edge_filter_90degree_8width_msa(dst, stride_dst,
                                                     src, stride_src,
                                                     sao_offset_val, height);
            dst += 8;
            src += 8;
            width %= 8;
        }

        if (width) {
            hevc_sao_edge_filter_90degree_4width_msa(dst, stride_dst,
                                                     src, stride_src,
                                                     sao_offset_val, height);
        }
        break;

    case 2:
        if (width >> 4) {
            hevc_sao_edge_filter_45degree_16multiple_msa(dst, stride_dst,
                                                         src, stride_src,
                                                         sao_offset_val,
                                                         width - (width % 16),
                                                         height);
            dst += width - (width % 16);
            src += width - (width % 16);
            width %= 16;
        }

        if (width >> 3) {
            hevc_sao_edge_filter_45degree_8width_msa(dst, stride_dst,
                                                     src, stride_src,
                                                     sao_offset_val, height);
            dst += 8;
            src += 8;
            width %= 8;
        }

        if (width) {
            hevc_sao_edge_filter_45degree_4width_msa(dst, stride_dst,
                                                     src, stride_src,
                                                     sao_offset_val, height);
        }
        break;

    case 3:
        if (width >> 4) {
            hevc_sao_edge_filter_135degree_16multiple_msa(dst, stride_dst,
                                                          src, stride_src,
                                                          sao_offset_val,
                                                          width - (width % 16),
                                                          height);
            dst += width - (width % 16);
            src += width - (width % 16);
            width %= 16;
        }

        if (width >> 3) {
            hevc_sao_edge_filter_135degree_8width_msa(dst, stride_dst,
                                                      src, stride_src,
                                                      sao_offset_val, height);
            dst += 8;
            src += 8;
            width %= 8;
        }

        if (width) {
            hevc_sao_edge_filter_135degree_4width_msa(dst, stride_dst,
                                                      src, stride_src,
                                                      sao_offset_val, height);
        }
        break;
    }
}