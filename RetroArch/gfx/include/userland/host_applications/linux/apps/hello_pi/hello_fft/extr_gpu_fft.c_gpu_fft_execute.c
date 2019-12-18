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
struct GPU_FFT {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPU_FFT_QPUS ; 
 int gpu_fft_base_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

unsigned gpu_fft_execute(struct GPU_FFT *info) {
    return gpu_fft_base_exec(&info->base, GPU_FFT_QPUS);
}