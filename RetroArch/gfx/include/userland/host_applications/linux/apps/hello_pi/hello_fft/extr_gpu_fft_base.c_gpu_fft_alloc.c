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
struct TYPE_2__ {scalar_t__ vptr; } ;
struct GPU_FFT_PTR {TYPE_1__ arm; scalar_t__ vc; } ;
struct GPU_FFT_HOST {unsigned int peri_size; scalar_t__ mem_map; int /*<<< orphan*/  peri_addr; int /*<<< orphan*/  mem_flg; } ;
struct GPU_FFT_BASE {unsigned int volatile* peri; unsigned int peri_size; int mb; unsigned int handle; unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_TO_PHYS (scalar_t__) ; 
 scalar_t__ gpu_fft_get_host_info (struct GPU_FFT_HOST*) ; 
 scalar_t__ mapmem (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int mem_alloc (int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_free (int,unsigned int) ; 
 scalar_t__ mem_lock (int,unsigned int) ; 
 scalar_t__ qpu_enable (int,int) ; 

int gpu_fft_alloc (
    int mb,
    unsigned size,
    struct GPU_FFT_PTR *ptr) {

    struct GPU_FFT_HOST host;
    struct GPU_FFT_BASE *base;
    volatile unsigned *peri;
    unsigned handle;

    if (gpu_fft_get_host_info(&host)) return -5;

    if (qpu_enable(mb, 1)) return -1;

    // Shared memory
    handle = mem_alloc(mb, size, 4096, host.mem_flg);
    if (!handle) {
        qpu_enable(mb, 0);
        return -3;
    }

    peri = (volatile unsigned *) mapmem(host.peri_addr, host.peri_size);
    if (!peri) {
        mem_free(mb, handle);
        qpu_enable(mb, 0);
        return -4;
    }

    ptr->vc = mem_lock(mb, handle);
    ptr->arm.vptr = mapmem(BUS_TO_PHYS(ptr->vc+host.mem_map), size);

    base = (struct GPU_FFT_BASE *) ptr->arm.vptr;
    base->peri      = peri;
    base->peri_size = host.peri_size;
    base->mb        = mb;
    base->handle    = handle;
    base->size      = size;

    return 0;
}