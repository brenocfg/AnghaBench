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
struct TYPE_3__ {int in_channels; int out_channels; int /*<<< orphan*/  downmix; } ;
typedef  TYPE_1__ AC3DSPContext ;

/* Variables and functions */
 int AV_CPU_FLAG_AVXSLOW ; 
 scalar_t__ EXTERNAL_AVX (int) ; 
 scalar_t__ EXTERNAL_FMA3 (int) ; 
 scalar_t__ EXTERNAL_SSE (int) ; 
 int av_get_cpu_flags () ; 
 int /*<<< orphan*/  ff_ac3_downmix_3_to_1_avx ; 
 int /*<<< orphan*/  ff_ac3_downmix_3_to_1_fma3 ; 
 int /*<<< orphan*/  ff_ac3_downmix_3_to_1_sse ; 
 int /*<<< orphan*/  ff_ac3_downmix_3_to_2_avx ; 
 int /*<<< orphan*/  ff_ac3_downmix_3_to_2_fma3 ; 
 int /*<<< orphan*/  ff_ac3_downmix_3_to_2_sse ; 
 int /*<<< orphan*/  ff_ac3_downmix_4_to_1_avx ; 
 int /*<<< orphan*/  ff_ac3_downmix_4_to_1_fma3 ; 
 int /*<<< orphan*/  ff_ac3_downmix_4_to_1_sse ; 
 int /*<<< orphan*/  ff_ac3_downmix_4_to_2_avx ; 
 int /*<<< orphan*/  ff_ac3_downmix_4_to_2_fma3 ; 
 int /*<<< orphan*/  ff_ac3_downmix_4_to_2_sse ; 
 int /*<<< orphan*/  ff_ac3_downmix_5_to_1_avx ; 
 int /*<<< orphan*/  ff_ac3_downmix_5_to_1_fma3 ; 
 int /*<<< orphan*/  ff_ac3_downmix_5_to_1_sse ; 
 int /*<<< orphan*/  ff_ac3_downmix_5_to_2_avx ; 
 int /*<<< orphan*/  ff_ac3_downmix_5_to_2_fma3 ; 
 int /*<<< orphan*/  ff_ac3_downmix_5_to_2_sse ; 
 int /*<<< orphan*/  ff_ac3_downmix_6_to_1_avx ; 
 int /*<<< orphan*/  ff_ac3_downmix_6_to_1_fma3 ; 
 int /*<<< orphan*/  ff_ac3_downmix_6_to_1_sse ; 
 int /*<<< orphan*/  ff_ac3_downmix_6_to_2_avx ; 
 int /*<<< orphan*/  ff_ac3_downmix_6_to_2_fma3 ; 
 int /*<<< orphan*/  ff_ac3_downmix_6_to_2_sse ; 

void ff_ac3dsp_set_downmix_x86(AC3DSPContext *c)
{
    int cpu_flags = av_get_cpu_flags();

#define SET_DOWNMIX(ch, suf, SUF)                                       \
    if (ch == c->in_channels) {                                         \
        if (EXTERNAL_ ## SUF (cpu_flags)) {                             \
            if (c->out_channels == 1)                                   \
                c->downmix = ff_ac3_downmix_ ## ch ## _to_1_ ## suf;    \
            else                                                        \
                c->downmix = ff_ac3_downmix_ ## ch ## _to_2_ ## suf;    \
        }                                                               \
    }

#define SET_DOWNMIX_ALL(suf, SUF)                   \
    SET_DOWNMIX(3, suf, SUF)                        \
    SET_DOWNMIX(4, suf, SUF)                        \
    SET_DOWNMIX(5, suf, SUF)                        \
    SET_DOWNMIX(6, suf, SUF)

    SET_DOWNMIX_ALL(sse,  SSE)
    if (!(cpu_flags & AV_CPU_FLAG_AVXSLOW)) {
        SET_DOWNMIX_ALL(avx,  AVX)
        SET_DOWNMIX_ALL(fma3, FMA3)
    }
}