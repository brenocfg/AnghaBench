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
struct G722Band {int scale_factor; scalar_t__ s_predictor; } ;
typedef  int /*<<< orphan*/  diff ;

/* Variables and functions */
 int av_clip_int16 (scalar_t__) ; 

__attribute__((used)) static inline int encode_high(const struct G722Band *state, int xhigh)
{
    int diff = av_clip_int16(xhigh - state->s_predictor);
    int pred = 141 * state->scale_factor >> 8;
           /* = diff >= 0 ? (diff < pred) + 2 : diff >= -pred */
    return ((diff ^ (diff >> (sizeof(diff)*8-1))) < pred) + 2*(diff >= 0);
}