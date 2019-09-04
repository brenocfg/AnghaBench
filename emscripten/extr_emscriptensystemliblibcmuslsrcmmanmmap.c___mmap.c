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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* MAP_FAILED ; 
 int MAP_FIXED ; 
 int OFF_MASK ; 
 size_t PTRDIFF_MAX ; 
 int /*<<< orphan*/  SYS_mmap ; 
 int /*<<< orphan*/  __vm_wait () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,void*,size_t,int,int,int,int) ; 

void *__mmap(void *start, size_t len, int prot, int flags, int fd, off_t off)
{
	if (off & OFF_MASK) {
		errno = EINVAL;
		return MAP_FAILED;
	}
	if (len >= PTRDIFF_MAX) {
		errno = ENOMEM;
		return MAP_FAILED;
	}
	if (flags & MAP_FIXED) {
		__vm_wait();
	}
#ifdef SYS_mmap2
	return (void *)syscall(SYS_mmap2, start, len, prot, flags, fd, off/UNIT);
#else
	return (void *)syscall(SYS_mmap, start, len, prot, flags, fd, off);
#endif
}