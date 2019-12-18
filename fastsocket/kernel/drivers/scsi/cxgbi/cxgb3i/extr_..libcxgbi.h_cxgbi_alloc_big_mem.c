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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 void* vmalloc (unsigned int) ; 

__attribute__((used)) static inline void *cxgbi_alloc_big_mem(unsigned int size,
					gfp_t gfp)
{
	void *p = kmalloc(size, gfp);
	if (!p)
		p = vmalloc(size);
	if (p)
		memset(p, 0, size);
	return p;
}