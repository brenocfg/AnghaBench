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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_EXPAND_OPTIONS_NONE ; 
 int /*<<< orphan*/  pmap_enter_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
pmap_enter(
	pmap_t		pmap,
 	vm_map_offset_t		vaddr,
	ppnum_t                 pn,
	vm_prot_t		prot,
	vm_prot_t		fault_type,
	unsigned int 		flags,
	boolean_t		wired)
{
	return pmap_enter_options(pmap, vaddr, pn, prot, fault_type, flags, wired, PMAP_EXPAND_OPTIONS_NONE, NULL);
}