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
 intptr_t PAGE_SIZE ; 
 int /*<<< orphan*/  exit (int) ; 
 int munmap (void*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void unmapmem(void *addr, unsigned size)
{
   const intptr_t offset = (intptr_t)addr % PAGE_SIZE;
   addr = (char *)addr - offset;
   size = size + offset;
   int s = munmap(addr, size);
   if (s != 0) {
      printf("munmap error %d\n", s);
      exit (-1);
   }
}