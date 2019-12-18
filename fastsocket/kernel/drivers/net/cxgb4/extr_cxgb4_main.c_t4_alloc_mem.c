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
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 void* vzalloc (size_t) ; 

void *t4_alloc_mem(size_t size)
{
	void *p = kzalloc(size, GFP_KERNEL);

	if (!p)
		p = vzalloc(size);
	return p;
}