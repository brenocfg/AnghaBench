#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_entry_t ;
typedef  TYPE_2__* vm_map_copy_t ;
struct vm_map_store {int dummy; } ;
struct rb_head {int dummy; } ;
struct vm_map_header {struct rb_head rb_head_store; } ;
struct TYPE_8__ {struct vm_map_header cpy_hdr; } ;
struct TYPE_7__ {struct TYPE_7__* vme_next; struct vm_map_store store; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,struct rb_head*,struct vm_map_store*) ; 
 int /*<<< orphan*/  rb_head ; 
 TYPE_1__* vm_map_copy_to_entry (TYPE_2__*) ; 

void
vm_map_store_copy_reset_rb( vm_map_copy_t copy, vm_map_entry_t entry, int nentries )
{
	struct vm_map_header *mapHdr = &(copy->cpy_hdr);
	struct rb_head *rbh = &(mapHdr->rb_head_store);
	struct vm_map_store *store;
	int deleted=0;
		
	while (entry != vm_map_copy_to_entry(copy) && nentries > 0) {		
		store = &(entry->store);
		RB_REMOVE( rb_head, rbh, store );
		entry = entry->vme_next;
		deleted++;
		nentries--;
	}
}