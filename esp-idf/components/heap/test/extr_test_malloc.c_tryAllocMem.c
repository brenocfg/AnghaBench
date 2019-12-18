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
 int** allocatedMem ; 
 void* malloc (int) ; 
 int noAllocated ; 

__attribute__((used)) static int tryAllocMem(void) {
    int i, j;
    const int allocateMaxK=1024*5; //try to allocate a max of 5MiB

    allocatedMem=malloc(sizeof(int *)*allocateMaxK);
    if (!allocatedMem) return 0;

    for (i=0; i<allocateMaxK; i++) {
        allocatedMem[i]=malloc(1024);
        if (allocatedMem[i]==NULL) break;
        for (j=0; j<1024/4; j++) allocatedMem[i][j]=(0xdeadbeef);
    }
    noAllocated=i;
    return i;
}