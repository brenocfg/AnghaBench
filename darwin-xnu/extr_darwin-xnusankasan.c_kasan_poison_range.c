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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kasan_poison (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
kasan_poison_range(vm_offset_t base, vm_size_t size, uint8_t flags)
{
	/* base must be 8-byte aligned */
	/* total region must cover 8-byte multiple */
	assert((base & 0x07) == 0);
	assert((size & 0x07) == 0);
	kasan_poison(base, 0, 0, size, flags);
}