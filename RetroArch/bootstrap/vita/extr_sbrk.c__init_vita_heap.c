#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SceKernelLwMutexWork {int dummy; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  size_user; } ;
typedef  TYPE_1__ SceKernelFreeMemorySizeInfo ;

/* Variables and functions */
 int /*<<< orphan*/  RAM_THRESHOLD ; 
 int _newlib_heap_base ; 
 int _newlib_heap_cur ; 
 int /*<<< orphan*/  _newlib_heap_end ; 
 scalar_t__ _newlib_heap_memblock ; 
 int /*<<< orphan*/  _newlib_heap_size ; 
 int /*<<< orphan*/  _newlib_heap_size_user ; 
 scalar_t__ _newlib_sbrk_mutex ; 
 scalar_t__ _newlib_vm_memblock ; 
 int _newlib_vm_size_user ; 
 scalar_t__ sceKernelAllocMemBlock (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sceKernelAllocMemBlockForVM (char*,int) ; 
 scalar_t__ sceKernelCreateLwMutex (struct SceKernelLwMutexWork*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelGetFreeMemorySize (TYPE_1__*) ; 
 scalar_t__ sceKernelGetMemBlockBase (scalar_t__,void**) ; 

void _init_vita_heap(void) {

	int _newlib_vm_size = 0;
	if (&_newlib_vm_size_user != NULL) {
		_newlib_vm_size = _newlib_vm_size_user;
	  _newlib_vm_memblock = sceKernelAllocMemBlockForVM("code", _newlib_vm_size_user);

	  if (_newlib_vm_memblock < 0){
	    //sceClibPrintf("sceKernelAllocMemBlockForVM failed\n");
			goto failure;
		}
	}else{
		_newlib_vm_memblock = 0;
	}

	// Create a mutex to use inside _sbrk_r
	if (sceKernelCreateLwMutex((struct SceKernelLwMutexWork*)_newlib_sbrk_mutex, "sbrk mutex", 0, 0, 0) < 0) {
		goto failure;
	}
	
	// Always allocating the max avaliable USER_RW mem on the system
	SceKernelFreeMemorySizeInfo info;
	info.size = sizeof(SceKernelFreeMemorySizeInfo);
	sceKernelGetFreeMemorySize(&info);

	if (&_newlib_heap_size_user != NULL) {
		_newlib_heap_size = _newlib_heap_size_user;
	}else{
		_newlib_heap_size = info.size_user - RAM_THRESHOLD;
	}

	_newlib_heap_size -= _newlib_vm_size;

	_newlib_heap_memblock = sceKernelAllocMemBlock("Newlib heap", 0x0c20d060, _newlib_heap_size, 0);
	if (_newlib_heap_memblock < 0) {
		goto failure;
	}
	if (sceKernelGetMemBlockBase(_newlib_heap_memblock, (void**)&_newlib_heap_base) < 0) {
		goto failure;
	}
	_newlib_heap_end = _newlib_heap_base + _newlib_heap_size;
	_newlib_heap_cur = _newlib_heap_base;

	return;
failure:
	_newlib_vm_memblock = 0;
	_newlib_heap_memblock = 0;
	_newlib_heap_base = 0;
	_newlib_heap_cur = 0;
}