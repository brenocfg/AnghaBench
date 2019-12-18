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
typedef  size_t u32 ;
struct bp_entry {int /*<<< orphan*/ * address; int /*<<< orphan*/  instr; struct bp_entry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPCODE ; 
 int /*<<< orphan*/  DCStoreRangeNoSync (void*,int) ; 
 size_t GEKKO_MAX_BP ; 
 int /*<<< orphan*/  ICInvalidateRange (void*,int) ; 
 int /*<<< orphan*/  _sync () ; 
 struct bp_entry* bp_entries ; 
 struct bp_entry* p_bpentries ; 

__attribute__((used)) static u32 insert_bp(void *mem)
{
	u32 i;
	struct bp_entry *p;

	for(i=0;i<GEKKO_MAX_BP;i++) {
		if(bp_entries[i].address == NULL) break;
	}
	if(i==GEKKO_MAX_BP) return 0;

	p = &bp_entries[i];
	p->next = p_bpentries;
	p->address = mem;
	p_bpentries = p;

	p->instr = *(p->address);
	*(p->address) = BPCODE;

	DCStoreRangeNoSync((void*)((u32)mem&~0x1f),32);
	ICInvalidateRange((void*)((u32)mem&~0x1f),32);
	_sync();

	return 1;
}