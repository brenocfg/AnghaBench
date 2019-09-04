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
typedef  scalar_t__ uint16_t ;
struct kasan_alloc_header {scalar_t__ crc; scalar_t__ user_size; scalar_t__ left_rz; scalar_t__ alloc_size; } ;

/* Variables and functions */
 scalar_t__ __nosan_crc16 (scalar_t__,void*,scalar_t__) ; 
 struct kasan_alloc_header* header_for_user_addr (scalar_t__) ; 

__attribute__((used)) static uint16_t
kasan_alloc_crc(vm_offset_t addr)
{
	struct kasan_alloc_header *h = header_for_user_addr(addr);
	vm_size_t rightrz = h->alloc_size - h->user_size - h->left_rz;

	uint16_t crc_orig = h->crc;
	h->crc = 0;

	uint16_t crc = 0;
	crc = __nosan_crc16(crc, (void *)(addr - h->left_rz), h->left_rz);
	crc = __nosan_crc16(crc, (void *)(addr + h->user_size), rightrz);

	h->crc = crc_orig;

	return crc;
}