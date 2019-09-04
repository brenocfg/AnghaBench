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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_IDCT8x8_COL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LD_SH8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_SH8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE8x8_SH_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gt8x8_cnst ; 

__attribute__((used)) static void hevc_idct_8x8_msa(int16_t *coeffs)
{
    const int16_t *filter = &gt8x8_cnst[0];
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7;

    LD_SH8(coeffs, 8, in0, in1, in2, in3, in4, in5, in6, in7);
    HEVC_IDCT8x8_COL(in0, in1, in2, in3, in4, in5, in6, in7, 7);
    TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7,
                       in0, in1, in2, in3, in4, in5, in6, in7);
    HEVC_IDCT8x8_COL(in0, in1, in2, in3, in4, in5, in6, in7, 12);
    TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7,
                       in0, in1, in2, in3, in4, in5, in6, in7);
    ST_SH8(in0, in1, in2, in3, in4, in5, in6, in7, coeffs, 8);
}