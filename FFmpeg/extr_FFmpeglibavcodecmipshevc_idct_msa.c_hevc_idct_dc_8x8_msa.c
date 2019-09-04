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
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ST_SH8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  __msa_fill_h (int) ; 

__attribute__((used)) static void hevc_idct_dc_8x8_msa(int16_t *coeffs)
{
    int32_t val;
    v8i16 dst;

    val = (coeffs[0] + 1) >> 1;
    val = (val + 32) >> 6;
    dst = __msa_fill_h(val);

    ST_SH8(dst, dst, dst, dst, dst, dst, dst, dst, coeffs, 8);
}