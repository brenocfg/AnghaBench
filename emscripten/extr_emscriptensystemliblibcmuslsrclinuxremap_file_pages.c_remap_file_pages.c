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
 int /*<<< orphan*/  SYS_remap_file_pages ; 
 int syscall (int /*<<< orphan*/ ,void*,size_t,int,size_t,int) ; 

int remap_file_pages(void *addr, size_t size, int prot, size_t pgoff, int flags)
{
	return syscall(SYS_remap_file_pages, addr, size, prot, pgoff, flags);
}