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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
struct kasan_alloc_header {scalar_t__ user_size; scalar_t__ left_rz; scalar_t__ alloc_size; } ;
typedef  void kasan_alloc_footer ;

/* Variables and functions */
 struct kasan_alloc_header* header_for_user_addr (scalar_t__) ; 

__attribute__((used)) static struct kasan_alloc_footer *
footer_for_user_addr(vm_offset_t addr, vm_size_t *size)
{
	struct kasan_alloc_header *h = header_for_user_addr(addr);
	vm_size_t rightrz = h->alloc_size - h->user_size - h->left_rz;
	*size = rightrz;
	return (void *)(addr + h->user_size);
}