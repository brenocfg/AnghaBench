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
 scalar_t__ HDRLEN_KMALLOC ; 
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static inline int rcu_use_vmalloc(int size)
{
	/* Too big for a single page? */
	if (HDRLEN_KMALLOC + size > PAGE_SIZE)
		return 1;
	return 0;
}