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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int BACKTRACE_MAXFRAMES ; 
 int backtrace (uintptr_t*,int) ; 
 int min (int,int) ; 
 uintptr_t vm_kernel_slid_base ; 

__attribute__((used)) static vm_size_t
kasan_alloc_bt(uint32_t *ptr, vm_size_t sz, vm_size_t skip)
{
	uintptr_t buf[BACKTRACE_MAXFRAMES];
	uintptr_t *bt = buf;

	sz /= sizeof(uint32_t);
	vm_size_t frames = sz;

	if (frames > 0) {
		frames = min(frames + skip, BACKTRACE_MAXFRAMES);
		frames = backtrace(bt, frames);

		while (frames > sz && skip > 0) {
			bt++;
			frames--;
			skip--;
		}

		/* only store the offset from kernel base, and cram that into 32
		 * bits */
		for (vm_size_t i = 0; i < frames; i++) {
			ptr[i] = (uint32_t)(bt[i] - vm_kernel_slid_base);
		}
	}
	return frames;
}