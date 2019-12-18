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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* sbc_analyze_4 ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ SBCDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_sbcdsp_analysis_consts_fixed4_simd_even ; 
 int /*<<< orphan*/  ff_sbcdsp_analysis_consts_fixed4_simd_odd ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sbc_analyze_4b_4s_simd(SBCDSPContext *s,
                                          int16_t *x, int32_t *out, int out_stride)
{
    /* Analyze blocks */
    s->sbc_analyze_4(x + 12, out, ff_sbcdsp_analysis_consts_fixed4_simd_odd);
    out += out_stride;
    s->sbc_analyze_4(x + 8, out, ff_sbcdsp_analysis_consts_fixed4_simd_even);
    out += out_stride;
    s->sbc_analyze_4(x + 4, out, ff_sbcdsp_analysis_consts_fixed4_simd_odd);
    out += out_stride;
    s->sbc_analyze_4(x + 0, out, ff_sbcdsp_analysis_consts_fixed4_simd_even);
}