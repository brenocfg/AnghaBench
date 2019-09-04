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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  addr64_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_TRACE (int,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PMAP__UNNEST ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRHIDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_unnest_options_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

kern_return_t
pmap_unnest_options(
	pmap_t grand,
	addr64_t vaddr,
	uint64_t size,
	unsigned int option)
{
	kern_return_t kr = KERN_FAILURE;

	PMAP_TRACE(2, PMAP_CODE(PMAP__UNNEST) | DBG_FUNC_START,
	           VM_KERNEL_ADDRHIDE(grand), VM_KERNEL_ADDRHIDE(vaddr));

	kr = pmap_unnest_options_internal(grand, vaddr, size, option);

	PMAP_TRACE(2, PMAP_CODE(PMAP__UNNEST) | DBG_FUNC_END, kr);

	return kr;
}