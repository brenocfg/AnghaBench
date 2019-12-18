#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dm_snapshot {int /*<<< orphan*/  pending; TYPE_2__* store; } ;
struct TYPE_7__ {int /*<<< orphan*/  old_chunk; } ;
struct dm_snap_pending_exception {TYPE_3__ e; int /*<<< orphan*/ * full_bio; scalar_t__ started; int /*<<< orphan*/  snapshot_bios; int /*<<< orphan*/  origin_bios; } ;
typedef  int /*<<< orphan*/  chunk_t ;
struct TYPE_6__ {TYPE_1__* type; } ;
struct TYPE_5__ {scalar_t__ (* prepare_exception ) (TYPE_2__*,TYPE_3__*) ;} ;

/* Variables and functions */
 struct dm_snap_pending_exception* __lookup_pending_exception (struct dm_snapshot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_insert_exception (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  free_pending_exception (struct dm_snap_pending_exception*) ; 
 scalar_t__ stub1 (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static struct dm_snap_pending_exception *
__find_pending_exception(struct dm_snapshot *s,
			 struct dm_snap_pending_exception *pe, chunk_t chunk)
{
	struct dm_snap_pending_exception *pe2;

	pe2 = __lookup_pending_exception(s, chunk);
	if (pe2) {
		free_pending_exception(pe);
		return pe2;
	}

	pe->e.old_chunk = chunk;
	bio_list_init(&pe->origin_bios);
	bio_list_init(&pe->snapshot_bios);
	pe->started = 0;
	pe->full_bio = NULL;

	if (s->store->type->prepare_exception(s->store, &pe->e)) {
		free_pending_exception(pe);
		return NULL;
	}

	dm_insert_exception(&s->pending, &pe->e);

	return pe;
}