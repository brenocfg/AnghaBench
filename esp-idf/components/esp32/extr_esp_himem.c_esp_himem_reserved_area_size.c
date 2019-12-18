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

/* Variables and functions */
 size_t CACHE_BLOCKSIZE ; 
 size_t SPIRAM_BANKSWITCH_RESERVE ; 

size_t esp_himem_reserved_area_size(void) {
    return CACHE_BLOCKSIZE * SPIRAM_BANKSWITCH_RESERVE;
}