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
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ user_size_t ;
typedef  scalar_t__ user_addr_t ;

/* Variables and functions */
 int B_READ ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int /*<<< orphan*/  current_map () ; 
 int vm_map_check_protection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_page_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

int
useracc(
	user_addr_t	addr,
	user_size_t	len,
	int	prot)
{
	vm_map_t	map;

	map = current_map();
	return (vm_map_check_protection(
			map,
			vm_map_trunc_page(addr,
					  vm_map_page_mask(map)),
			vm_map_round_page(addr+len,
					  vm_map_page_mask(map)),
			prot == B_READ ? VM_PROT_READ : VM_PROT_WRITE));
}