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
 int MAP_ANON ; 
 void* MAP_FAILED ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 int PROT_NONE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 void* mmap (void*,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pages_unmap (void*,size_t) ; 

__attribute__((used)) static bool
pages_commit_impl(void *addr, size_t size, bool commit)
{

#ifndef _WIN32
	/*
	 * The following decommit/commit implementation is functional, but
	 * always disabled because it doesn't add value beyong improved
	 * debugging (at the cost of extra system calls) on systems that
	 * overcommit.
	 */
	if (false) {
		int prot = commit ? (PROT_READ | PROT_WRITE) : PROT_NONE;
		void *result = mmap(addr, size, prot, MAP_PRIVATE | MAP_ANON |
		    MAP_FIXED, -1, 0);
		if (result == MAP_FAILED)
			return (true);
		if (result != addr) {
			/*
			 * We succeeded in mapping memory, but not in the right
			 * place.
			 */
			pages_unmap(result, size);
			return (true);
		}
		return (false);
	}
#endif
	return (true);
}