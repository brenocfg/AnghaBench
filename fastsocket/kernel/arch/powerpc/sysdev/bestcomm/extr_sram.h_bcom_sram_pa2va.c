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
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {void* base_virt; scalar_t__ base_phys; } ;

/* Variables and functions */
 TYPE_1__* bcom_sram ; 

__attribute__((used)) static inline void *bcom_sram_pa2va(phys_addr_t pa) {
	return bcom_sram->base_virt +
		(unsigned long)(pa - bcom_sram->base_phys);
}