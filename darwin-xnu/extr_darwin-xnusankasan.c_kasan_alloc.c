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
typedef  int vm_size_t ;
typedef  int vm_offset_t ;
typedef  int vm_address_t ;
struct kasan_alloc_header {int left_rz; int alloc_size; int user_size; int /*<<< orphan*/  crc; int /*<<< orphan*/  frames; int /*<<< orphan*/  magic; } ;
struct kasan_alloc_footer {int /*<<< orphan*/  backtrace; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASAN_HEAP_RZ ; 
 int /*<<< orphan*/  LIVE_XOR ; 
 int /*<<< orphan*/  assert (int) ; 
 struct kasan_alloc_footer* footer_for_user_addr (int,int*) ; 
 struct kasan_alloc_header* header_for_user_addr (int) ; 
 int /*<<< orphan*/  kasan_alloc_bt (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kasan_alloc_crc (int) ; 
 int /*<<< orphan*/  kasan_poison (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_rz_clobber (int,int,int,int) ; 
 int /*<<< orphan*/  magic_for_addr (int,int /*<<< orphan*/ ) ; 

vm_address_t
kasan_alloc(vm_offset_t addr, vm_size_t size, vm_size_t req, vm_size_t leftrz)
{
	if (!addr) {
		return 0;
	}
	assert(size > 0);
	assert((addr % 8) == 0);
	assert((size % 8) == 0);

	vm_size_t rightrz = size - req - leftrz;

	kasan_poison(addr, req, leftrz, rightrz, ASAN_HEAP_RZ);
	kasan_rz_clobber(addr, req, leftrz, rightrz);

	addr += leftrz;

	/* stash the allocation sizes in the left redzone */
	struct kasan_alloc_header *h = header_for_user_addr(addr);
	h->magic = magic_for_addr(addr, LIVE_XOR);
	h->left_rz = leftrz;
	h->alloc_size = size;
	h->user_size = req;

	/* ... and a backtrace in the right redzone */
	vm_size_t fsize;
	struct kasan_alloc_footer *f = footer_for_user_addr(addr, &fsize);
	h->frames = kasan_alloc_bt(f->backtrace, fsize, 2);

	/* checksum the whole object, minus the user part */
	h->crc = kasan_alloc_crc(addr);

	return addr;
}