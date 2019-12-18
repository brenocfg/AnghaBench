#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int shared; int unique; int passes; } ;

/* Variables and functions */
 TYPE_1__* shaders ; 

int gpu_fft_twiddle_size(int log2_N, int *shared, int *unique, int *passes) {
    if (log2_N<8 || log2_N>22) return -1;
    *shared = shaders[log2_N-8].shared;
    *unique = shaders[log2_N-8].unique;
    *passes = shaders[log2_N-8].passes;
    return 0;
}