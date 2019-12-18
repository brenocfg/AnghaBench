#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* upl_t ;
typedef  int /*<<< orphan*/  upl_size_t ;
typedef  char uint64_t ;
typedef  TYPE_3__* thread_t ;
struct upl_page_info {int dummy; } ;
struct upl {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * decmp_upl; } ;
struct TYPE_7__ {scalar_t__ prev; scalar_t__ next; } ;
struct TYPE_8__ {int flags; int ref_count; char* upl_reprio_info; char* upl_commit_records; int /*<<< orphan*/ * upl_create_retaddr; scalar_t__ upl_commit_index; scalar_t__ upl_state; scalar_t__ ubc_alias2; scalar_t__ ubc_alias1; TYPE_1__ uplq; void* upl_creator; scalar_t__ decmp_io_upl; int /*<<< orphan*/  upl_priority; int /*<<< orphan*/ * upl_iodone; int /*<<< orphan*/ * associated_upl; int /*<<< orphan*/ * vector_upl; scalar_t__ highest_page; scalar_t__ ext_ref_count; int /*<<< orphan*/ * map_object; scalar_t__ size; scalar_t__ kaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSBacktrace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_POLICY_IO ; 
 int UPL_CREATE_EXPEDITE_SUP ; 
 int UPL_CREATE_INTERNAL ; 
 int UPL_CREATE_IO_TRACKING ; 
 int UPL_CREATE_LITE ; 
 int /*<<< orphan*/  UPL_DEBUG_STACK_FRAMES ; 
 int UPL_EXPEDITE_SUPPORTED ; 
 int UPL_INTERNAL ; 
 int UPL_LITE ; 
 int UPL_TRACKED_BY_OBJECT ; 
 int atop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 void* current_thread () ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  proc_get_effective_thread_policy (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_page_32 (int /*<<< orphan*/ ) ; 
 scalar_t__ upl_debug_enabled ; 
 int /*<<< orphan*/  upl_lock_init (TYPE_2__*) ; 
 int /*<<< orphan*/  upl_set_decmp_info (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static upl_t
upl_create(int type, int flags, upl_size_t size)
{
	upl_t	upl;
	vm_size_t	page_field_size = 0;
	int	upl_flags = 0;
	vm_size_t	upl_size  = sizeof(struct upl);

	size = round_page_32(size);

	if (type & UPL_CREATE_LITE) {
		page_field_size = (atop(size) + 7) >> 3;
		page_field_size = (page_field_size + 3) & 0xFFFFFFFC;

		upl_flags |= UPL_LITE;
	}
	if (type & UPL_CREATE_INTERNAL) {
		upl_size += sizeof(struct upl_page_info) * atop(size);

		upl_flags |= UPL_INTERNAL;
	}
	upl = (upl_t)kalloc(upl_size + page_field_size);

	if (page_field_size)
	        bzero((char *)upl + upl_size, page_field_size);

	upl->flags = upl_flags | flags;
	upl->kaddr = (vm_offset_t)0;
	upl->size = 0;
	upl->map_object = NULL;
	upl->ref_count = 1;
	upl->ext_ref_count = 0;
	upl->highest_page = 0;
	upl_lock_init(upl);
	upl->vector_upl = NULL;
	upl->associated_upl = NULL;
	upl->upl_iodone = NULL;
#if CONFIG_IOSCHED
	if (type & UPL_CREATE_IO_TRACKING) {
		upl->upl_priority = proc_get_effective_thread_policy(current_thread(), TASK_POLICY_IO);
	}

	upl->upl_reprio_info = 0;
	upl->decmp_io_upl = 0;
	if ((type & UPL_CREATE_INTERNAL) && (type & UPL_CREATE_EXPEDITE_SUP)) {
		/* Only support expedite on internal UPLs */
		thread_t        curthread = current_thread();
		upl->upl_reprio_info = (uint64_t *)kalloc(sizeof(uint64_t) * atop(size));
		bzero(upl->upl_reprio_info, (sizeof(uint64_t) * atop(size)));
		upl->flags |= UPL_EXPEDITE_SUPPORTED;
		if (curthread->decmp_upl != NULL)
			upl_set_decmp_info(upl, curthread->decmp_upl);
	}
#endif
#if CONFIG_IOSCHED || UPL_DEBUG
	if ((type & UPL_CREATE_IO_TRACKING) || upl_debug_enabled) {
		upl->upl_creator = current_thread();
		upl->uplq.next = 0;
		upl->uplq.prev = 0;
		upl->flags |= UPL_TRACKED_BY_OBJECT;
	}
#endif

#if UPL_DEBUG
	upl->ubc_alias1 = 0;
	upl->ubc_alias2 = 0;

	upl->upl_state = 0;
	upl->upl_commit_index = 0;
	bzero(&upl->upl_commit_records[0], sizeof(upl->upl_commit_records));

	(void) OSBacktrace(&upl->upl_create_retaddr[0], UPL_DEBUG_STACK_FRAMES);
#endif /* UPL_DEBUG */

	return(upl);
}