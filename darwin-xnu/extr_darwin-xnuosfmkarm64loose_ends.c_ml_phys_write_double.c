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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  pmap_paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ml_phys_write_data (int /*<<< orphan*/ ,unsigned long long,int) ; 

void ml_phys_write_double(vm_offset_t paddr, unsigned long long data)
{
        ml_phys_write_data((pmap_paddr_t)paddr, data, 8);
}