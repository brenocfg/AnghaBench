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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  hevc_idct_dc_8x8_msa (int /*<<< orphan*/ *) ; 

void ff_hevc_idct_dc_8x8_msa(int16_t *coeffs)
{
    hevc_idct_dc_8x8_msa(coeffs);
}