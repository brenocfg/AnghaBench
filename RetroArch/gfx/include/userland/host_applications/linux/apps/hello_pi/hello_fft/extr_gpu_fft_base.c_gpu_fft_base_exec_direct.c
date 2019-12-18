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
struct GPU_FFT_BASE {int* peri; int* vc_unifs; int vc_code; } ;

/* Variables and functions */
 size_t V3D_DBCFG ; 
 size_t V3D_DBQITC ; 
 size_t V3D_DBQITE ; 
 size_t V3D_L2CACTL ; 
 size_t V3D_SLCACTL ; 
 size_t V3D_SRQCS ; 
 size_t V3D_SRQPC ; 
 size_t V3D_SRQUA ; 

unsigned gpu_fft_base_exec_direct (
    struct GPU_FFT_BASE *base,
    int num_qpus) {

    unsigned q, t;

    base->peri[V3D_DBCFG] = 0; // Disallow IRQ
    base->peri[V3D_DBQITE] = 0; // Disable IRQ
    base->peri[V3D_DBQITC] = -1; // Resets IRQ flags

    base->peri[V3D_L2CACTL] =  1<<2; // Clear L2 cache
    base->peri[V3D_SLCACTL] = -1; // Clear other caches

    base->peri[V3D_SRQCS] = (1<<7) | (1<<8) | (1<<16); // Reset error bit and counts

    for (q=0; q<num_qpus; q++) { // Launch shader(s)
        base->peri[V3D_SRQUA] = base->vc_unifs[q];
        base->peri[V3D_SRQPC] = base->vc_code;
    }

    // Busy wait polling
    for (;;) {
        if (((base->peri[V3D_SRQCS]>>16) & 0xff) == num_qpus) break; // All done?
    }

    return 0;
}