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
typedef  int uint8_t ;

/* Variables and functions */
 int av_clip_uint8 (int) ; 

__attribute__((used)) static inline uint8_t ana_convert(const int *coeff, const uint8_t *left, const uint8_t *right)
{
    int sum;

    sum  = coeff[0] * left[0] + coeff[3] * right[0]; //red in
    sum += coeff[1] * left[1] + coeff[4] * right[1]; //green in
    sum += coeff[2] * left[2] + coeff[5] * right[2]; //blue in

    return av_clip_uint8(sum >> 16);
}