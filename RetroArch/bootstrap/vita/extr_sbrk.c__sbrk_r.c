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
struct _reent {int /*<<< orphan*/  _errno; } ;
struct SceKernelLwMutexWork {int dummy; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  _newlib_heap_base ; 
 scalar_t__ _newlib_heap_cur ; 
 scalar_t__ _newlib_heap_end ; 
 scalar_t__ _newlib_sbrk_mutex ; 
 scalar_t__ sceKernelLockLwMutex (struct SceKernelLwMutexWork*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelUnlockLwMutex (struct SceKernelLwMutexWork*,int) ; 

void * _sbrk_r(struct _reent *reent, ptrdiff_t incr) {
	if (sceKernelLockLwMutex((struct SceKernelLwMutexWork*)_newlib_sbrk_mutex, 1, 0) < 0)
		goto fail;
	if (!_newlib_heap_base || _newlib_heap_cur + incr >= _newlib_heap_end) {
		sceKernelUnlockLwMutex((struct SceKernelLwMutexWork*)_newlib_sbrk_mutex, 1);
fail:
		reent->_errno = ENOMEM;
		return (void*)-1;
	}

	char *prev_heap_end = _newlib_heap_cur;
	_newlib_heap_cur += incr;

	sceKernelUnlockLwMutex((struct SceKernelLwMutexWork*)_newlib_sbrk_mutex, 1);
	return (void*) prev_heap_end;
}