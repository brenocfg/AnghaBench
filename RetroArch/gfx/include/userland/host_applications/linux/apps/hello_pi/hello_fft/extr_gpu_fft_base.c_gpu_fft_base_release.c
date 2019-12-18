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
struct GPU_FFT_BASE {int mb; unsigned int handle; unsigned int size; unsigned int peri_size; scalar_t__ peri; } ;

/* Variables and functions */
 int /*<<< orphan*/  mem_free (int,unsigned int) ; 
 int /*<<< orphan*/  mem_unlock (int,unsigned int) ; 
 int /*<<< orphan*/  qpu_enable (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmapmem (void*,unsigned int) ; 

void gpu_fft_base_release(struct GPU_FFT_BASE *base) {
    int mb = base->mb;
    unsigned handle = base->handle, size = base->size;
    unmapmem((void*)base->peri, base->peri_size);
    unmapmem((void*)base, size);
    mem_unlock(mb, handle);
    mem_free(mb, handle);
    qpu_enable(mb, 0);
}