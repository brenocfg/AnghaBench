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
typedef  int vm_size_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int alloc_ptepages_count ; 
 int inuse_ptepages_count ; 
 int vm_page_active_count ; 
 int vm_page_free_count ; 
 int vm_page_inactive_count ; 

void
pt_fake_zone_info(
	int		*count,
	vm_size_t	*cur_size,
	vm_size_t	*max_size,
	vm_size_t	*elem_size,
	vm_size_t	*alloc_size,
	uint64_t	*sum_size,
	int		*collectable,
	int		*exhaustable,
	int		*caller_acct)
{
        *count      = inuse_ptepages_count;
	*cur_size   = PAGE_SIZE * inuse_ptepages_count;
	*max_size   = PAGE_SIZE * (inuse_ptepages_count +
				   vm_page_inactive_count +
				   vm_page_active_count +
				   vm_page_free_count);
	*elem_size  = PAGE_SIZE;
	*alloc_size = PAGE_SIZE;
	*sum_size = alloc_ptepages_count * PAGE_SIZE;

	*collectable = 1;
	*exhaustable = 0;
	*caller_acct = 1;
}