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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;

/* Variables and functions */
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  pmap_map_high_window_bd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

vm_map_address_t
ml_map_high_window(
	vm_offset_t	phys_addr,
	vm_size_t	len)
{
	return pmap_map_high_window_bd(phys_addr, len, VM_PROT_READ | VM_PROT_WRITE);
}