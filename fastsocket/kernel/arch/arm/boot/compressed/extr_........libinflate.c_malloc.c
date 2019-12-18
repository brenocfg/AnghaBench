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
 int /*<<< orphan*/  error (char*) ; 
 int free_mem_end_ptr ; 
 int free_mem_ptr ; 
 int /*<<< orphan*/  malloc_count ; 
 int malloc_ptr ; 

__attribute__((used)) static void *malloc(int size)
{
       void *p;

       if (size < 0)
		error("Malloc error");
       if (!malloc_ptr)
		malloc_ptr = free_mem_ptr;

       malloc_ptr = (malloc_ptr + 3) & ~3;     /* Align */

       p = (void *)malloc_ptr;
       malloc_ptr += size;

       if (free_mem_end_ptr && malloc_ptr >= free_mem_end_ptr)
		error("Out of memory");

       malloc_count++;
       return p;
}