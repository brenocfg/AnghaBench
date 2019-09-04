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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/ * kalloc (size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,size_t) ; 

kern_return_t
kalloc_test()
{
	uint64_t * data_ptr;
	size_t alloc_size;

	T_LOG("Running kalloc test.\n");

	alloc_size = sizeof(uint64_t);
	data_ptr = kalloc(alloc_size);
	T_ASSERT_NOTNULL(data_ptr, "kalloc sizeof(uint64_t) return not null");
	kfree(data_ptr, alloc_size);

	alloc_size = 3544;
	data_ptr = kalloc(alloc_size);
	T_ASSERT_NOTNULL(data_ptr, "kalloc 3544 return not null");
	kfree(data_ptr, alloc_size);

	return KERN_SUCCESS;
}