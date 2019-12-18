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
struct GPU_FFT_HOST {unsigned int peri_addr; unsigned int peri_size; int mem_flg; int mem_map; } ;

/* Variables and functions */
 scalar_t__ GPU_FFT_USE_VC4_L2_CACHE ; 
 int /*<<< orphan*/  RTLD_LAZY ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 void* dlsym (void*,char*) ; 

int gpu_fft_get_host_info(struct GPU_FFT_HOST *info) {
    void *handle;
    unsigned (*bcm_host_get_sdram_address)     (void);
    unsigned (*bcm_host_get_peripheral_address)(void);
    unsigned (*bcm_host_get_peripheral_size)   (void);

    // Pi 1 defaults
    info->peri_addr = 0x20000000;
    info->peri_size = 0x01000000;
    info->mem_flg = GPU_FFT_USE_VC4_L2_CACHE? 0xC : 0x4;
    info->mem_map = GPU_FFT_USE_VC4_L2_CACHE? 0x0 : 0x20000000; // Pi 1 only

    handle = dlopen("libbcm_host.so", RTLD_LAZY);
    if (!handle) return -1;

    *(void **) (&bcm_host_get_sdram_address)      = dlsym(handle, "bcm_host_get_sdram_address");
    *(void **) (&bcm_host_get_peripheral_address) = dlsym(handle, "bcm_host_get_peripheral_address");
    *(void **) (&bcm_host_get_peripheral_size)    = dlsym(handle, "bcm_host_get_peripheral_size");

    if (bcm_host_get_sdram_address && bcm_host_get_sdram_address()!=0x40000000) { // Pi 2?
        info->mem_flg = 0x4; // ARM cannot see VC4 L2 on Pi 2
        info->mem_map = 0x0;
    }

    if (bcm_host_get_peripheral_address) info->peri_addr = bcm_host_get_peripheral_address();
    if (bcm_host_get_peripheral_size)    info->peri_size = bcm_host_get_peripheral_size();

    dlclose(handle);
    return 0;
}