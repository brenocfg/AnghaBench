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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPLY_VERT_QPEL_NO_ROUND_FILTER_8BYTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_UB2 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB4 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __msa_ldi_b (int) ; 

__attribute__((used)) static void vert_mc_qpel_no_rnd_8x8_msa(const uint8_t *src,
                                        int32_t src_stride,
                                        uint8_t *dst,
                                        int32_t dst_stride)
{
    v16u8 inp0, inp1, inp2, inp3, inp4, inp5, inp6, inp7, inp8;
    v16u8 res0, res1;
    v16u8 const20 = (v16u8) __msa_ldi_b(20);
    v16u8 const6 = (v16u8) __msa_ldi_b(6);
    v16u8 const3 = (v16u8) __msa_ldi_b(3);

    LD_UB4(src, src_stride, inp0, inp1, inp2, inp3);
    src += (4 * src_stride);
    LD_UB2(src, src_stride, inp4, inp5);
    src += (2 * src_stride);
    res0 = APPLY_VERT_QPEL_NO_ROUND_FILTER_8BYTE(inp0, inp0, inp1, inp2,
                                                 inp1, inp2, inp3, inp4,
                                                 inp1, inp0, inp0, inp1,
                                                 inp2, inp3, inp4, inp5,
                                                 const20, const6, const3);
    LD_UB2(src, src_stride, inp6, inp7);
    src += (2 * src_stride);
    res1 = APPLY_VERT_QPEL_NO_ROUND_FILTER_8BYTE(inp2, inp1, inp0, inp0,
                                                 inp3, inp4, inp5, inp6,
                                                 inp3, inp2, inp1, inp0,
                                                 inp4, inp5, inp6, inp7,
                                                 const20, const6, const3);
    ST_D4(res0, res1, 0, 1, 0, 1, dst, dst_stride);

    inp8 = LD_UB(src);
    res0 = APPLY_VERT_QPEL_NO_ROUND_FILTER_8BYTE(inp4, inp3, inp2, inp1,
                                                 inp5, inp6, inp7, inp8,
                                                 inp5, inp4, inp3, inp2,
                                                 inp6, inp7, inp8, inp8,
                                                 const20, const6, const3);
    res1 = APPLY_VERT_QPEL_NO_ROUND_FILTER_8BYTE(inp6, inp5, inp4, inp3,
                                                 inp7, inp8, inp8, inp7,
                                                 inp7, inp6, inp5, inp4,
                                                 inp8, inp8, inp7, inp6,
                                                 const20, const6, const3);
    ST_D4(res0, res1, 0, 1, 0, 1, dst + 4 * dst_stride, dst_stride);
}