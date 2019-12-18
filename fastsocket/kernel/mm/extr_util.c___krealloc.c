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
 void* ZERO_SIZE_PTR ; 
 void* kmalloc_track_caller (size_t,int /*<<< orphan*/ ) ; 
 size_t ksize (void const*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 scalar_t__ unlikely (int) ; 

void *__krealloc(const void *p, size_t new_size, gfp_t flags)
{
	void *ret;
	size_t ks = 0;

	if (unlikely(!new_size))
		return ZERO_SIZE_PTR;

	if (p)
		ks = ksize(p);

	if (ks >= new_size)
		return (void *)p;

	ret = kmalloc_track_caller(new_size, flags);
	if (ret && p)
		memcpy(ret, p, ks);

	return ret;
}