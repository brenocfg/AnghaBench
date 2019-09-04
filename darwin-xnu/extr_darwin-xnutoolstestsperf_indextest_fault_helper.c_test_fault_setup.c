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
 char* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int MEMSIZE ; 
 int PERFINDEX_SUCCESS ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  VERIFY (int,char*) ; 
 int getpagesize () ; 
 char* memblock ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int mprotect (char*,int,int) ; 

int test_fault_setup() {
    char *ptr;
    int pgsz = getpagesize();
    int retval;

    memblock = (char *)mmap(NULL, MEMSIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    VERIFY(memblock != MAP_FAILED, "mmap failed");

    /* make sure memory is paged */
    for(ptr = memblock; ptr<memblock+MEMSIZE; ptr+= pgsz) {
        *ptr = 1;
    }

    /* set to read only, then back to read write so it faults on first write */
    retval = mprotect(memblock, MEMSIZE, PROT_READ);
    VERIFY(retval == 0, "mprotect failed");

    retval = mprotect(memblock, MEMSIZE, PROT_READ | PROT_WRITE);
    VERIFY(retval == 0, "mprotect failed");

    return PERFINDEX_SUCCESS;
}