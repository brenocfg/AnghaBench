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
 int* low_quant ; 

__attribute__((used)) static inline int encode_low(const struct G722Band* state, int xlow)
{
    int diff  = av_clip_int16(xlow - state->s_predictor);
           /* = diff >= 0 ? diff : -(diff + 1) */
    int limit = diff ^ (diff >> (sizeof(diff)*8-1));
    int i = 0;
    limit = limit + 1 << 10;
    if (limit > low_quant[8] * state->scale_factor)
        i = 9;
    while (i < 29 && limit > low_quant[i] * state->scale_factor)
        i++;
    return (diff < 0 ? (i < 2 ? 63 : 33) : 61) - i;
}