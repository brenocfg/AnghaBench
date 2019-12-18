#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8u16 ;
typedef  scalar_t__ v4u32 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  scalar_t__ v2u64 ;
typedef  int /*<<< orphan*/  v2i64 ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT_D2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  LD (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __msa_copy_u_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_hadd_u_d (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_hadd_u_h (TYPE_1__,TYPE_1__) ; 
 scalar_t__ __msa_hadd_u_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_pckev_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_splati_b (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_srari_w (int /*<<< orphan*/ ,int) ; 

void ff_dc_8x8_msa(uint8_t *dst, ptrdiff_t dst_stride, const uint8_t *src_left,
                   const uint8_t *src_top)
{
    uint64_t val0, val1;
    v16i8 store;
    v16u8 src = { 0 };
    v8u16 sum_h;
    v4u32 sum_w;
    v2u64 sum_d;

    val0 = LD(src_top);
    val1 = LD(src_left);
    INSERT_D2_UB(val0, val1, src);
    sum_h = __msa_hadd_u_h(src, src);
    sum_w = __msa_hadd_u_w(sum_h, sum_h);
    sum_d = __msa_hadd_u_d(sum_w, sum_w);
    sum_w = (v4u32) __msa_pckev_w((v4i32) sum_d, (v4i32) sum_d);
    sum_d = __msa_hadd_u_d(sum_w, sum_w);
    sum_w = (v4u32) __msa_srari_w((v4i32) sum_d, 4);
    store = __msa_splati_b((v16i8) sum_w, 0);
    val0 = __msa_copy_u_d((v2i64) store, 0);

    SD4(val0, val0, val0, val0, dst, dst_stride);
    dst += (4 * dst_stride);
    SD4(val0, val0, val0, val0, dst, dst_stride);
}