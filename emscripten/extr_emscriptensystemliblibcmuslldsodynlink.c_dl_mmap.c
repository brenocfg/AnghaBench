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

/* Variables and functions */
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SYS_mmap ; 
 scalar_t__ __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *dl_mmap(size_t n)
{
	void *p;
	int prot = PROT_READ|PROT_WRITE, flags = MAP_ANONYMOUS|MAP_PRIVATE;
#ifdef SYS_mmap2
	p = (void *)__syscall(SYS_mmap2, 0, n, prot, flags, -1, 0);
#else
	p = (void *)__syscall(SYS_mmap, 0, n, prot, flags, -1, 0);
#endif
	return p == MAP_FAILED ? 0 : p;
}