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
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,unsigned int) ; 
 unsigned int getpagesize () ; 
 void* mmap (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open_or_die (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *map_zeroed_pages(unsigned int num)
{
	int fd = open_or_die("/dev/zero", O_RDONLY);
	void *addr;

	/*
	 * We use a private mapping (ie. if we write to the page, it will be
	 * copied).
	 */
	addr = mmap(NULL, getpagesize() * num,
		    PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE, fd, 0);
	if (addr == MAP_FAILED)
		err(1, "Mmaping %u pages of /dev/zero", num);

	/*
	 * One neat mmap feature is that you can close the fd, and it
	 * stays mapped.
	 */
	close(fd);

	return addr;
}