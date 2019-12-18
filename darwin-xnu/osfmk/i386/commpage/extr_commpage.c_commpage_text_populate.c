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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  commpage_descriptor ;

/* Variables and functions */
 int INTEL_PGBYTES ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int _COMM_PAGE_TEXT_AREA_USED ; 
 scalar_t__ _COMM_PAGE_TEXT_END ; 
 int /*<<< orphan*/  _COMM_PAGE_TEXT_START ; 
 int _cpu_capabilities ; 
 int /*<<< orphan*/  commPageBaseOffset ; 
 char* commPagePtr ; 
 char* commPageTextPtr32 ; 
 char* commPageTextPtr64 ; 
 int /*<<< orphan*/ ** commpage_32_routines ; 
 int /*<<< orphan*/ ** commpage_64_routines ; 
 scalar_t__ commpage_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  commpage_stuff_routine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  commpage_text32_map ; 
 int /*<<< orphan*/  commpage_text64_map ; 
 int k64Bit ; 
 scalar_t__ next ; 
 int /*<<< orphan*/  panic (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  pmap_commpage32_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_commpage64_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void commpage_text_populate( void ){
	commpage_descriptor **rd;
	
	next = 0;
	commPagePtr = (char *) commpage_allocate(commpage_text32_map, (vm_size_t) _COMM_PAGE_TEXT_AREA_USED, VM_PROT_READ | VM_PROT_EXECUTE);
	commPageTextPtr32 = commPagePtr;
	
	char *cptr = commPagePtr;
	int i=0;
	for(; i< _COMM_PAGE_TEXT_AREA_USED; i++){
		cptr[i]=0xCC;
	}
	
	commPageBaseOffset = _COMM_PAGE_TEXT_START;
	for (rd = commpage_32_routines; *rd != NULL; rd++) {
		commpage_stuff_routine(*rd);
	}

#ifndef __LP64__
	pmap_commpage32_init((vm_offset_t) commPageTextPtr32, _COMM_PAGE_TEXT_START, 
			   _COMM_PAGE_TEXT_AREA_USED/INTEL_PGBYTES);
#endif	

	if (_cpu_capabilities & k64Bit) {
		next = 0;
		commPagePtr = (char *) commpage_allocate(commpage_text64_map, (vm_size_t) _COMM_PAGE_TEXT_AREA_USED, VM_PROT_READ | VM_PROT_EXECUTE);
		commPageTextPtr64 = commPagePtr;

		cptr=commPagePtr;
		for(i=0; i<_COMM_PAGE_TEXT_AREA_USED; i++){
			cptr[i]=0xCC;
		}

		for (rd = commpage_64_routines; *rd !=NULL; rd++) {
			commpage_stuff_routine(*rd);
		}

#ifndef __LP64__
	pmap_commpage64_init((vm_offset_t) commPageTextPtr64, _COMM_PAGE_TEXT_START, 
			   _COMM_PAGE_TEXT_AREA_USED/INTEL_PGBYTES);
#endif	
	}

	if (next > _COMM_PAGE_TEXT_END) 
		panic("commpage text overflow: next=0x%08x, commPagePtr=%p", next, commPagePtr); 

}