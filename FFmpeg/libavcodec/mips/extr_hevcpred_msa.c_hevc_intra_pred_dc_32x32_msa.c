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
typedef  scalar_t__ v8u16 ;
typedef  int /*<<< orphan*/  v4u32 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HADD_UB2_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_UB2 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_UB2 (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __msa_hadd_u_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_hadd_u_w (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_pckev_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_splati_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_srari_w (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hevc_intra_pred_dc_32x32_msa(const uint8_t *src_top,
                                         const uint8_t *src_left,
                                         uint8_t *dst, int32_t stride)
{
    uint32_t row;
    v16u8 src_above1, src_above2, store, src_left1, src_left2;
    v8u16 sum_above1, sum_above2;
    v8u16 sum_left1, sum_left2;
    v8u16 sum, sum_above, sum_left;

    LD_UB2(src_top, 16, src_above1, src_above2);
    LD_UB2(src_left, 16, src_left1, src_left2);
    HADD_UB2_UH(src_above1, src_above2, sum_above1, sum_above2);
    HADD_UB2_UH(src_left1, src_left2, sum_left1, sum_left2);
    sum_above = sum_above1 + sum_above2;
    sum_left = sum_left1 + sum_left2;
    sum = sum_above + sum_left;
    sum = (v8u16) __msa_hadd_u_w(sum, sum);
    sum = (v8u16) __msa_hadd_u_d((v4u32) sum, (v4u32) sum);
    sum = (v8u16) __msa_pckev_w((v4i32) sum, (v4i32) sum);
    sum = (v8u16) __msa_hadd_u_d((v4u32) sum, (v4u32) sum);
    sum = (v8u16) __msa_srari_w((v4i32) sum, 6);
    store = (v16u8) __msa_splati_b((v16i8) sum, 0);

    for (row = 16; row--;) {
        ST_UB2(store, store, dst, 16);
        dst += stride;
        ST_UB2(store, store, dst, 16);
        dst += stride;
    }
}