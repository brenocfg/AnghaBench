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
typedef  int /*<<< orphan*/  v8i16 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HSUB_UB4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_SH8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void diff_pixels_msa(int16_t *block, const uint8_t *src1,
                            const uint8_t *src2, int32_t stride)
{
    v16u8 in10, in11, in12, in13, in14, in15, in16, in17;
    v16u8 in20, in21, in22, in23, in24, in25, in26, in27;
    v8i16 out0, out1, out2, out3, out4, out5, out6, out7;

    LD_UB8(src1, stride, in10, in11, in12, in13, in14, in15, in16, in17);
    LD_UB8(src2, stride, in20, in21, in22, in23, in24, in25, in26, in27);
    ILVR_B4_SH(in10, in20, in11, in21, in12, in22, in13, in23,
               out0, out1, out2, out3);
    ILVR_B4_SH(in14, in24, in15, in25, in16, in26, in17, in27,
               out4, out5, out6, out7);
    HSUB_UB4_SH(out0, out1, out2, out3, out0, out1, out2, out3);
    HSUB_UB4_SH(out4, out5, out6, out7, out4, out5, out6, out7);
    ST_SH8(out0, out1, out2, out3, out4, out5, out6, out7, block, 8);
}