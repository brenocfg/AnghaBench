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
struct TYPE_2__ {int /*<<< orphan*/  (* twiddles ) (int,float*) ;} ;

/* Variables and functions */
 int GPU_FFT_FWD ; 
 int GPU_FFT_PI ; 
 TYPE_1__* shaders ; 
 int /*<<< orphan*/  stub1 (int,float*) ; 

void gpu_fft_twiddle_data(int log2_N, int direction, float *out) {
    shaders[log2_N-8].twiddles((direction==GPU_FFT_FWD?-2:2)*GPU_FFT_PI, out);
}