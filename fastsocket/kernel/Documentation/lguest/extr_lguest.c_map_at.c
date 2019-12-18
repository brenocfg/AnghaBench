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
typedef  unsigned long ssize_t ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  err (int,char*,unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ mmap (void*,unsigned long,int,int,int,unsigned long) ; 
 unsigned long pread (int,void*,unsigned long,unsigned long) ; 

__attribute__((used)) static void map_at(int fd, void *addr, unsigned long offset, unsigned long len)
{
	ssize_t r;

	/*
	 * We map writable even though for some segments are marked read-only.
	 * The kernel really wants to be writable: it patches its own
	 * instructions.
	 *
	 * MAP_PRIVATE means that the page won't be copied until a write is
	 * done to it.  This allows us to share untouched memory between
	 * Guests.
	 */
	if (mmap(addr, len, PROT_READ|PROT_WRITE|PROT_EXEC,
		 MAP_FIXED|MAP_PRIVATE, fd, offset) != MAP_FAILED)
		return;

	/* pread does a seek and a read in one shot: saves a few lines. */
	r = pread(fd, addr, len, offset);
	if (r != len)
		err(1, "Reading offset %lu len %lu gave %zi", offset, len, r);
}