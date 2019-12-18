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
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 void* vmalloc (unsigned int) ; 

__attribute__((used)) static inline void * alloc_fdmem(unsigned int size)
{
	if (size <= PAGE_SIZE)
		return kmalloc(size, GFP_KERNEL);
	else
		return vmalloc(size);
}