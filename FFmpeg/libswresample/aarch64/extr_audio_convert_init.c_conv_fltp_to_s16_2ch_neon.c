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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  swri_oldapi_conv_fltp_to_s16_2ch_neon (int /*<<< orphan*/ *,float* const*,int,int) ; 

__attribute__((used)) static void conv_fltp_to_s16_2ch_neon(uint8_t **dst, const uint8_t **src, int len){
    swri_oldapi_conv_fltp_to_s16_2ch_neon((int16_t*)*dst, (float *const*)src, len, 2);
}