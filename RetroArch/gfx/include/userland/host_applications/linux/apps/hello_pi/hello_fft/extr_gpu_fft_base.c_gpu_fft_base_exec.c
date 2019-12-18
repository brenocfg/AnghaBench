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
struct GPU_FFT_BASE {scalar_t__ vc_msg; int /*<<< orphan*/  mb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPU_FFT_NO_FLUSH ; 
 int /*<<< orphan*/  GPU_FFT_TIMEOUT ; 
 int execute_qpu (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpu_fft_base_exec_direct (struct GPU_FFT_BASE*,int) ; 

unsigned gpu_fft_base_exec(
    struct GPU_FFT_BASE *base,
    int num_qpus) {

    if (base->vc_msg) {
        // Use mailbox
        // Returns: 0x0 for success; 0x80000000 for timeout
        return execute_qpu(base->mb, num_qpus, base->vc_msg, GPU_FFT_NO_FLUSH, GPU_FFT_TIMEOUT);
    }
    else {
        // Direct register poking
        return gpu_fft_base_exec_direct(base, num_qpus);
    }
}