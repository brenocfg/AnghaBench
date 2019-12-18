#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {unsigned char* swap_map; unsigned long lowest_bit; unsigned long highest_bit; scalar_t__ prio; size_t type; int flags; TYPE_4__* bdev; int /*<<< orphan*/  inuse_pages; } ;
struct gendisk {TYPE_1__* fops; } ;
struct TYPE_8__ {struct gendisk* bd_disk; } ;
struct TYPE_7__ {scalar_t__ prio; } ;
struct TYPE_6__ {size_t next; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* swap_slot_free_notify ) (TYPE_4__*,unsigned long) ;} ;

/* Variables and functions */
 unsigned char COUNT_CONTINUED ; 
 unsigned char SWAP_HAS_CACHE ; 
 unsigned char SWAP_MAP_MAX ; 
 unsigned char SWAP_MAP_SHMEM ; 
 int SWP_BLKDEV ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_swap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_swap_pages ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,unsigned long) ; 
 scalar_t__ swap_count_continued (struct swap_info_struct*,unsigned long,unsigned char) ; 
 TYPE_3__** swap_info ; 
 TYPE_2__ swap_list ; 
 unsigned long swp_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char swap_entry_free(struct swap_info_struct *p,
				     swp_entry_t entry, unsigned char usage)
{
	unsigned long offset = swp_offset(entry);
	unsigned char count;
	unsigned char has_cache;

	count = p->swap_map[offset];
	has_cache = count & SWAP_HAS_CACHE;
	count &= ~SWAP_HAS_CACHE;

	if (usage == SWAP_HAS_CACHE) {
		VM_BUG_ON(!has_cache);
		has_cache = 0;
	} else if (count == SWAP_MAP_SHMEM) {
		/*
		 * Or we could insist on shmem.c using a special
		 * swap_shmem_free() and free_shmem_swap_and_cache()...
		 */
		count = 0;
	} else if ((count & ~COUNT_CONTINUED) <= SWAP_MAP_MAX) {
		if (count == COUNT_CONTINUED) {
			if (swap_count_continued(p, offset, count))
				count = SWAP_MAP_MAX | COUNT_CONTINUED;
			else
				count = SWAP_MAP_MAX;
		} else
			count--;
	}

	if (!count)
		mem_cgroup_uncharge_swap(entry);

	usage = count | has_cache;
	p->swap_map[offset] = usage;

	/* free if no reference */
	if (!usage) {
		struct gendisk *disk = p->bdev->bd_disk;
		if (offset < p->lowest_bit)
			p->lowest_bit = offset;
		if (offset > p->highest_bit)
			p->highest_bit = offset;
		if (swap_list.next >= 0 &&
		    p->prio > swap_info[swap_list.next]->prio)
			swap_list.next = p->type;
		nr_swap_pages++;
		p->inuse_pages--;
		if ((p->flags & SWP_BLKDEV) &&
				disk->fops->swap_slot_free_notify)
			disk->fops->swap_slot_free_notify(p->bdev, offset);
	}

	return usage;
}