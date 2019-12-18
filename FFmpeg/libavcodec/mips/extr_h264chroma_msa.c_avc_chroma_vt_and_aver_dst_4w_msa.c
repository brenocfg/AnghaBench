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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  avc_chroma_vt_and_aver_dst_4x2_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avc_chroma_vt_and_aver_dst_4x4_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avc_chroma_vt_and_aver_dst_4x8_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void avc_chroma_vt_and_aver_dst_4w_msa(uint8_t *src, uint8_t *dst,
                                              int32_t stride, uint32_t coeff0,
                                              uint32_t coeff1, int32_t height)
{
    if (2 == height) {
        avc_chroma_vt_and_aver_dst_4x2_msa(src, dst, stride, coeff0, coeff1);
    } else if (4 == height) {
        avc_chroma_vt_and_aver_dst_4x4_msa(src, dst, stride, coeff0, coeff1);
    } else if (8 == height) {
        avc_chroma_vt_and_aver_dst_4x8_msa(src, dst, stride, coeff0, coeff1);
    }
}