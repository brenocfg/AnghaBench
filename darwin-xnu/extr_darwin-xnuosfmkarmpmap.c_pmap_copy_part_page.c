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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  addr64_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ptoa (int /*<<< orphan*/ ) ; 

void
pmap_copy_part_page(
	ppnum_t psrc,
	vm_offset_t src_offset,
	ppnum_t pdst,
	vm_offset_t dst_offset,
	vm_size_t len)
{
	bcopy_phys((addr64_t) (ptoa(psrc) + src_offset),
	      (addr64_t) (ptoa(pdst) + dst_offset),
	      len);
}