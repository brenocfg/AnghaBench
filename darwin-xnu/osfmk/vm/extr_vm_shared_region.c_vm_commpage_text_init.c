#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_named_entry_t ;
typedef  scalar_t__ user64_addr_t ;
typedef  scalar_t__ user32_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  map; } ;
struct TYPE_12__ {TYPE_1__ backing; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; } ;
struct TYPE_11__ {TYPE_2__ backing; } ;
struct TYPE_10__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 scalar_t__ _COMM_PAGE32_TEXT_START ; 
 scalar_t__ _COMM_PAGE64_TEXT_START ; 
 int /*<<< orphan*/  _COMM_PAGE_TEXT_AREA_LENGTH ; 
 unsigned int _PFZ32_SLIDE_RANGE ; 
 unsigned int _PFZ64_SLIDE_RANGE ; 
 int /*<<< orphan*/  _vm_commpage_init (TYPE_3__**,int /*<<< orphan*/ ) ; 
 TYPE_6__* commpage_text32_entry ; 
 TYPE_3__* commpage_text32_handle ; 
 scalar_t__ commpage_text32_location ; 
 int /*<<< orphan*/  commpage_text32_map ; 
 TYPE_4__* commpage_text64_entry ; 
 TYPE_3__* commpage_text64_handle ; 
 scalar_t__ commpage_text64_location ; 
 int /*<<< orphan*/  commpage_text64_map ; 
 int /*<<< orphan*/  commpage_text_populate () ; 
 unsigned int random () ; 

void
vm_commpage_text_init(void)
{
	SHARED_REGION_TRACE_DEBUG(
		("commpage text: ->init()\n"));
#if defined(__i386__) || defined(__x86_64__)
	/* create the 32 bit comm text page */
	unsigned int offset = (random() % _PFZ32_SLIDE_RANGE) << PAGE_SHIFT; /* restricting to 32bMAX-2PAGE */
	_vm_commpage_init(&commpage_text32_handle, _COMM_PAGE_TEXT_AREA_LENGTH);
	commpage_text32_entry = (vm_named_entry_t) commpage_text32_handle->ip_kobject;
	commpage_text32_map = commpage_text32_entry->backing.map;
	commpage_text32_location = (user32_addr_t) (_COMM_PAGE32_TEXT_START + offset);
	/* XXX if (cpu_is_64bit_capable()) ? */
        /* create the 64-bit comm page */
	offset = (random() % _PFZ64_SLIDE_RANGE) << PAGE_SHIFT; /* restricting sliding upto 2Mb range */
        _vm_commpage_init(&commpage_text64_handle, _COMM_PAGE_TEXT_AREA_LENGTH);
        commpage_text64_entry = (vm_named_entry_t) commpage_text64_handle->ip_kobject;
        commpage_text64_map = commpage_text64_entry->backing.map;
	commpage_text64_location = (user64_addr_t) (_COMM_PAGE64_TEXT_START + offset);

	commpage_text_populate();
#elif defined(__arm64__) || defined(__arm__)
#else
#error Unknown architecture.
#endif /* __i386__ || __x86_64__ */
	/* populate the routines in here */
	SHARED_REGION_TRACE_DEBUG(
                ("commpage text: init() <-\n"));

}