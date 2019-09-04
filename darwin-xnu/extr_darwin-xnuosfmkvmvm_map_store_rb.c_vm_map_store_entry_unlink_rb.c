#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_entry_t ;
struct vm_map_store {int dummy; } ;
struct rb_head {int dummy; } ;
struct vm_map_header {struct rb_head rb_head_store; } ;
struct TYPE_3__ {struct vm_map_store store; } ;

/* Variables and functions */
 struct vm_map_store* RB_FIND (int /*<<< orphan*/ ,struct rb_head*,struct vm_map_store*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,struct rb_head*,struct vm_map_store*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rb_head ; 

void	vm_map_store_entry_unlink_rb( struct vm_map_header *mapHdr, vm_map_entry_t entry)
{
	struct rb_head *rbh = &(mapHdr->rb_head_store);
	struct vm_map_store *rb_entry;
	struct vm_map_store *store = &(entry->store);
	
	rb_entry = RB_FIND( rb_head, rbh, store);	
	if(rb_entry == NULL)
		panic("NO ENTRY TO DELETE");
	RB_REMOVE( rb_head, rbh, store );
}