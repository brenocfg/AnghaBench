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
 scalar_t__ ml_phys_read_data (int /*<<< orphan*/ ,int) ; 

unsigned int ml_phys_read_word(vm_offset_t paddr) {

        return (unsigned int)ml_phys_read_data((pmap_paddr_t)paddr, 4);
}