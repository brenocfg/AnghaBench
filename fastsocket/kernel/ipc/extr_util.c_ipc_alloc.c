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
 int PAGE_SIZE ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* vmalloc (int) ; 

void* ipc_alloc(int size)
{
	void* out;
	if(size > PAGE_SIZE)
		out = vmalloc(size);
	else
		out = kmalloc(size, GFP_KERNEL);
	return out;
}