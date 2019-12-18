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
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_8__ {int lg_maxobjs; size_t curobjs; size_t first; int /*<<< orphan*/ * objs; int /*<<< orphan*/  curbytes; } ;
typedef  TYPE_1__ quarantine_t ;
typedef  int /*<<< orphan*/  quarantine_obj_t ;

/* Variables and functions */
 size_t ZU (int) ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  quarantine_drain_one (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* quarantine_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcache_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tsd_quarantine_set (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static quarantine_t *
quarantine_grow(tsd_t *tsd, quarantine_t *quarantine)
{
	quarantine_t *ret;

	ret = quarantine_init(tsd, quarantine->lg_maxobjs + 1);
	if (ret == NULL) {
		quarantine_drain_one(tsd, quarantine);
		return (quarantine);
	}

	ret->curbytes = quarantine->curbytes;
	ret->curobjs = quarantine->curobjs;
	if (quarantine->first + quarantine->curobjs <= (ZU(1) <<
	    quarantine->lg_maxobjs)) {
		/* objs ring buffer data are contiguous. */
		memcpy(ret->objs, &quarantine->objs[quarantine->first],
		    quarantine->curobjs * sizeof(quarantine_obj_t));
	} else {
		/* objs ring buffer data wrap around. */
		size_t ncopy_a = (ZU(1) << quarantine->lg_maxobjs) -
		    quarantine->first;
		size_t ncopy_b = quarantine->curobjs - ncopy_a;

		memcpy(ret->objs, &quarantine->objs[quarantine->first], ncopy_a
		    * sizeof(quarantine_obj_t));
		memcpy(&ret->objs[ncopy_a], quarantine->objs, ncopy_b *
		    sizeof(quarantine_obj_t));
	}
	idalloctm(tsd, quarantine, tcache_get(tsd, false), true);

	tsd_quarantine_set(tsd, ret);
	return (ret);
}