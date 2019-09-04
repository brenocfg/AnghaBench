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
typedef  int /*<<< orphan*/ * ff_scene_sad_fn ;

/* Variables and functions */

ff_scene_sad_fn ff_scene_sad_get_fn_x86(int depth)
{
#if HAVE_X86ASM
    int cpu_flags = av_get_cpu_flags();
    if (depth == 8) {
#if HAVE_AVX2_EXTERNAL
        if (EXTERNAL_AVX2_FAST(cpu_flags))
            return scene_sad_avx2;
#endif
        if (EXTERNAL_SSE2(cpu_flags))
            return scene_sad_sse2;
    }
#endif
    return NULL;
}