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
typedef  int v8i16 ;
typedef  int /*<<< orphan*/ * v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD2 (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  CLIP_SH2_0_255 (int,int) ; 
 int /*<<< orphan*/ * LD_UB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ST_UB (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUB2 (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  UNPCK_UB_SH (int /*<<< orphan*/ *,int,int) ; 
 int __msa_fill_h (int /*<<< orphan*/  const) ; 
 scalar_t__ __msa_pckev_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hevc_intra_pred_vert_16x16_msa(const uint8_t *src_top,
                                           const uint8_t *src_left,
                                           uint8_t *dst, int32_t stride,
                                           int32_t flag)
{
    int32_t col;
    uint8_t *tmp_dst = dst;
    uint32_t row;
    v16u8 src;
    v8i16 vec0, vec1, vec2, vec3;

    src = LD_UB(src_top);

    for (row = 16; row--;) {
        ST_UB(src, tmp_dst);
        tmp_dst += stride;
    }

    if (0 == flag) {
        src = LD_UB(src_left);

        vec0 = __msa_fill_h(src_left[-1]);
        vec1 = __msa_fill_h(src_top[0]);

        UNPCK_UB_SH(src, vec2, vec3);
        SUB2(vec2, vec0, vec3, vec0, vec2, vec3);

        vec2 >>= 1;
        vec3 >>= 1;

        ADD2(vec2, vec1, vec3, vec1, vec2, vec3);
        CLIP_SH2_0_255(vec2, vec3);

        src = (v16u8) __msa_pckev_b((v16i8) vec3, (v16i8) vec2);

        for (col = 0; col < 16; col++) {
            dst[stride * col] = src[col];
        }
    }
}