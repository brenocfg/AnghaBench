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
 int /*<<< orphan*/  kfree (void const*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,size_t) ; 

__attribute__((used)) static void *Realloc(const void *oldmem, size_t newlen, size_t oldlen)
{
	void *newmem = kmalloc(newlen, GFP_KERNEL);

	if (newmem && oldmem)
		memcpy(newmem, oldmem, min(oldlen, newlen));
	kfree(oldmem);
	return newmem;
}