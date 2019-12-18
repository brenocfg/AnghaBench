#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_size_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
struct pmap {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_flush_context ;
typedef  int /*<<< orphan*/  chunk_state_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {scalar_t__ vo_shadow_offset; struct TYPE_8__* shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CHUNK_NOT_COMPLETE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHUNK_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deactivate_pages_in_object (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct pmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_paging_begin (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_paging_end (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 

__attribute__((used)) static vm_object_size_t
deactivate_a_chunk(
	vm_object_t		orig_object,
	vm_object_offset_t	offset,
	vm_object_size_t	size,
	boolean_t               kill_page,
	boolean_t		reusable_page,
	boolean_t		all_reusable,
	pmap_flush_context      *pfc,
	struct pmap		*pmap,
	vm_map_offset_t		pmap_offset)
{
	vm_object_t		object;
	vm_object_t		tmp_object;
	vm_object_size_t	length;
	chunk_state_t		chunk_state;


	/*
	 * Get set to do a chunk.  We'll do up to CHUNK_SIZE, but no more than the
	 * remaining size the caller asked for.
	 */

	length = MIN(size, CHUNK_SIZE);

	/*
	 * The chunk_state keeps track of which pages we've already processed if there's
	 * a shadow chain on this object.  At this point, we haven't done anything with this
	 * range of pages yet, so initialize the state to indicate no pages processed yet.
	 */

	CHUNK_INIT(chunk_state, length);
	object = orig_object;

	/*
	 * Start at the top level object and iterate around the loop once for each object
	 * in the shadow chain.  We stop processing early if we've already found all the pages
	 * in the range.  Otherwise we stop when we run out of shadow objects.
	 */

	while (object && CHUNK_NOT_COMPLETE(chunk_state)) {
		vm_object_paging_begin(object);

		deactivate_pages_in_object(object, offset, length, kill_page, reusable_page, all_reusable, &chunk_state, pfc, pmap, pmap_offset);

		vm_object_paging_end(object);

		/*
		 * We've finished with this object, see if there's a shadow object.  If
		 * there is, update the offset and lock the new object.  We also turn off
		 * kill_page at this point since we only kill pages in the top most object.
		 */

		tmp_object = object->shadow;

		if (tmp_object) {
			kill_page = FALSE;
			reusable_page = FALSE;
			all_reusable = FALSE;
		        offset += object->vo_shadow_offset;
		        vm_object_lock(tmp_object);
		}

		if (object != orig_object)
		        vm_object_unlock(object);

		object = tmp_object;
	}

	if (object && object != orig_object)
	        vm_object_unlock(object);

	return length;
}