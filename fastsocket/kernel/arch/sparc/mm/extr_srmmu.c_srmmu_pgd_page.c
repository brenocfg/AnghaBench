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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int SRMMU_PTD_PMASK ; 
 scalar_t__ __nocache_va (int) ; 
 int pgd_val (int /*<<< orphan*/ ) ; 
 scalar_t__ srmmu_device_memory (int) ; 

__attribute__((used)) static inline unsigned long srmmu_pgd_page(pgd_t pgd)
{ return srmmu_device_memory(pgd_val(pgd))?~0:(unsigned long)__nocache_va((pgd_val(pgd) & SRMMU_PTD_PMASK) << 4); }