#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  memory_object_t ;
typedef  int /*<<< orphan*/  compressor_slot_t ;
typedef  TYPE_2__* compressor_pager_t ;
struct TYPE_6__ {int /*<<< orphan*/ * cpgr_eslots; int /*<<< orphan*/ * cpgr_dslots; int /*<<< orphan*/ ** cpgr_islots; } ;
struct TYPE_7__ {int cpgr_num_slots; TYPE_1__ cpgr_slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPRESSOR_SLOTS_CHUNK_SIZE ; 
 int COMPRESSOR_SLOTS_PER_CHUNK ; 
 int /*<<< orphan*/  compressor_pager_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  compressor_pager_lookup (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ compressor_pager_slots_chunk_free (int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  compressor_pager_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

unsigned int
vm_compressor_pager_reap_pages(
	memory_object_t		mem_obj,
	int			flags)
{
	compressor_pager_t	pager;
	int			num_chunks;
	int			failures;
	int			i;
	compressor_slot_t	*chunk;
	unsigned int		num_slots_freed;

	compressor_pager_lookup(mem_obj, pager);
	if (pager == NULL)
		return 0;

	compressor_pager_lock(pager);

	/* reap the compressor slots */
	num_slots_freed = 0;

	num_chunks = (pager->cpgr_num_slots + COMPRESSOR_SLOTS_PER_CHUNK -1) / COMPRESSOR_SLOTS_PER_CHUNK;
	if (num_chunks > 1) {
		/* we have an array of chunks */
		for (i = 0; i < num_chunks; i++) {
			chunk = pager->cpgr_slots.cpgr_islots[i];
			if (chunk != NULL) {
				num_slots_freed +=
					compressor_pager_slots_chunk_free(
						chunk,
						COMPRESSOR_SLOTS_PER_CHUNK,
						flags,
						&failures);
				if (failures == 0) {
					pager->cpgr_slots.cpgr_islots[i] = NULL;
					kfree(chunk, COMPRESSOR_SLOTS_CHUNK_SIZE);
				}
			}
		}
	} else if (pager->cpgr_num_slots > 2) {
		chunk = pager->cpgr_slots.cpgr_dslots;
		num_slots_freed +=
			compressor_pager_slots_chunk_free(
				chunk,
				pager->cpgr_num_slots,
				flags,
				NULL);
	} else {
		chunk = &pager->cpgr_slots.cpgr_eslots[0];
		num_slots_freed +=
			compressor_pager_slots_chunk_free(
				chunk,
				pager->cpgr_num_slots,
				flags,
				NULL);
	}

	compressor_pager_unlock(pager);

	return num_slots_freed;
}