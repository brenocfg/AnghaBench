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
struct SceKernelLwMutexWork {int dummy; } ;

/* Variables and functions */
 scalar_t__ _newlib_heap_base ; 
 scalar_t__ _newlib_heap_cur ; 
 scalar_t__ _newlib_heap_memblock ; 
 scalar_t__ _newlib_sbrk_mutex ; 
 scalar_t__ _newlib_vm_memblock ; 
 int /*<<< orphan*/  sceKernelDeleteLwMutex (struct SceKernelLwMutexWork*) ; 
 int /*<<< orphan*/  sceKernelFreeMemBlock (scalar_t__) ; 

void _free_vita_heap(void) {

	// Destroy the sbrk mutex
	sceKernelDeleteLwMutex((struct SceKernelLwMutexWork*)_newlib_sbrk_mutex);

	// Free the heap memblock to avoid memory leakage.
	sceKernelFreeMemBlock(_newlib_heap_memblock);

	if(_newlib_vm_memblock)
  	sceKernelFreeMemBlock(_newlib_vm_memblock);

	_newlib_vm_memblock = 0;
	_newlib_heap_memblock = 0;
	_newlib_heap_base = 0;
	_newlib_heap_cur = 0;
}