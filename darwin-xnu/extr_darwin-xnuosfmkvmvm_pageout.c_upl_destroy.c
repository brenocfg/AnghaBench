#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vector_upl_t ;
typedef  TYPE_1__* upl_t ;
struct upl_page_info {int dummy; } ;
struct upl {int dummy; } ;
struct TYPE_6__ {int flags; int size; scalar_t__ vector_upl; int /*<<< orphan*/  map_object; scalar_t__ ext_ref_count; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int UPL_DEVICE_MEMORY ; 
 int UPL_INTERNAL ; 
 int UPL_LITE ; 
 int UPL_SHADOWED ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  upl_lock_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
upl_destroy(upl_t upl)
{
	int	page_field_size;  /* bit field in word size buf */
        int	size;

	if (upl->ext_ref_count) {
		panic("upl(%p) ext_ref_count", upl);
	}

#if CONFIG_IOSCHED
        if ((upl->flags & UPL_DECMP_REAL_IO) && upl->decmp_io_upl) {
                upl_t src_upl;
                src_upl = upl->decmp_io_upl;
                assert((src_upl->flags & UPL_DECMP_REQ) != 0);
                upl_lock(src_upl);
                src_upl->decmp_io_upl = NULL;
                upl_unlock(src_upl);
                upl_deallocate(src_upl);
        }
#endif /* CONFIG_IOSCHED */

#if CONFIG_IOSCHED || UPL_DEBUG
	if ((upl->flags & UPL_TRACKED_BY_OBJECT) && !(upl->flags & UPL_VECTOR)) {
		vm_object_t	object;

		if (upl->flags & UPL_SHADOWED) {
			object = upl->map_object->shadow;
		} else {
			object = upl->map_object;
		}

		vm_object_lock(object);
		queue_remove(&object->uplq, upl, upl_t, uplq);
		vm_object_activity_end(object);
		vm_object_collapse(object, 0, TRUE);
		vm_object_unlock(object);
	}
#endif
	/*
	 * drop a reference on the map_object whether or
	 * not a pageout object is inserted
	 */
	if (upl->flags & UPL_SHADOWED)
		vm_object_deallocate(upl->map_object);

        if (upl->flags & UPL_DEVICE_MEMORY)
	        size = PAGE_SIZE;
	else
	        size = upl->size;
	page_field_size = 0;

	if (upl->flags & UPL_LITE) {
		page_field_size = ((size/PAGE_SIZE) + 7) >> 3;
		page_field_size = (page_field_size + 3) & 0xFFFFFFFC;
	}
	upl_lock_destroy(upl);
	upl->vector_upl = (vector_upl_t) 0xfeedbeef;

#if CONFIG_IOSCHED
	if (upl->flags & UPL_EXPEDITE_SUPPORTED)
		kfree(upl->upl_reprio_info, sizeof(uint64_t) * (size/PAGE_SIZE));
#endif

	if (upl->flags & UPL_INTERNAL) {
		kfree(upl,
		      sizeof(struct upl) +
		      (sizeof(struct upl_page_info) * (size/PAGE_SIZE))
		      + page_field_size);
	} else {
		kfree(upl, sizeof(struct upl) + page_field_size);
	}
}