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
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_7__ {size_t curbytes; int curobjs; int lg_maxobjs; int first; TYPE_2__* objs; } ;
typedef  TYPE_1__ quarantine_t ;
struct TYPE_8__ {size_t usize; void* ptr; } ;
typedef  TYPE_2__ quarantine_obj_t ;

/* Variables and functions */
 size_t SMALL_MAXCLASS ; 
 int ZU (int) ; 
 int /*<<< orphan*/  arena_quarantine_junk_small (void*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cassert (scalar_t__) ; 
 scalar_t__ config_fill ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  config_valgrind ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_valgrind ; 
 size_t isalloc (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 int /*<<< orphan*/  opt_junk_free ; 
 size_t opt_quarantine ; 
 int /*<<< orphan*/  quarantine_drain (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 TYPE_1__* quarantine_grow (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* tsd_quarantine_get (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void
quarantine(tsd_t *tsd, void *ptr)
{
	quarantine_t *quarantine;
	size_t usize = isalloc(ptr, config_prof);

	cassert(config_fill);
	assert(opt_quarantine);

	if ((quarantine = tsd_quarantine_get(tsd)) == NULL) {
		idalloctm(tsd, ptr, NULL, false);
		return;
	}
	/*
	 * Drain one or more objects if the quarantine size limit would be
	 * exceeded by appending ptr.
	 */
	if (quarantine->curbytes + usize > opt_quarantine) {
		size_t upper_bound = (opt_quarantine >= usize) ? opt_quarantine
		    - usize : 0;
		quarantine_drain(tsd, quarantine, upper_bound);
	}
	/* Grow the quarantine ring buffer if it's full. */
	if (quarantine->curobjs == (ZU(1) << quarantine->lg_maxobjs))
		quarantine = quarantine_grow(tsd, quarantine);
	/* quarantine_grow() must free a slot if it fails to grow. */
	assert(quarantine->curobjs < (ZU(1) << quarantine->lg_maxobjs));
	/* Append ptr if its size doesn't exceed the quarantine size. */
	if (quarantine->curbytes + usize <= opt_quarantine) {
		size_t offset = (quarantine->first + quarantine->curobjs) &
		    ((ZU(1) << quarantine->lg_maxobjs) - 1);
		quarantine_obj_t *obj = &quarantine->objs[offset];
		obj->ptr = ptr;
		obj->usize = usize;
		quarantine->curbytes += usize;
		quarantine->curobjs++;
		if (config_fill && unlikely(opt_junk_free)) {
			/*
			 * Only do redzone validation if Valgrind isn't in
			 * operation.
			 */
			if ((!config_valgrind || likely(!in_valgrind))
			    && usize <= SMALL_MAXCLASS)
				arena_quarantine_junk_small(ptr, usize);
			else
				memset(ptr, 0x5a, usize);
		}
	} else {
		assert(quarantine->curbytes == 0);
		idalloctm(tsd, ptr, NULL, false);
	}
}