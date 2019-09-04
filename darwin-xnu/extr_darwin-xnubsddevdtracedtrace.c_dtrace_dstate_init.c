#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* dtdv_next; } ;
typedef  TYPE_2__ dtrace_dynvar_t ;
typedef  int /*<<< orphan*/  dtrace_dynhash_t ;
struct TYPE_10__ {size_t dtds_chunksize; size_t dtds_size; size_t dtds_hashsize; TYPE_2__* dtdsc_free; struct TYPE_10__* dtds_percpu; TYPE_1__* dtds_hash; TYPE_1__* dtds_base; } ;
typedef  TYPE_3__ dtrace_dstate_t ;
typedef  int /*<<< orphan*/  dtrace_dstate_percpu_t ;
struct TYPE_11__ {scalar_t__ dtdv_hashval; } ;
struct TYPE_8__ {TYPE_5__* dtdh_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DTRACE_DYNHASH_SINK ; 
 size_t DTRACE_DYNVAR_CHUNKSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KM_NOSLEEP ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int LONG_MAX ; 
 size_t NCPU ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 TYPE_5__ dtrace_dynhash_sink ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_state_cache ; 
 TYPE_3__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kmem_zalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_dstate_init(dtrace_dstate_t *dstate, size_t size)
{
	size_t hashsize, maxper, min_size, chunksize = dstate->dtds_chunksize;
	void *base;
	uintptr_t limit;
	dtrace_dynvar_t *dvar, *next, *start;
	size_t i;

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);
	ASSERT(dstate->dtds_base == NULL && dstate->dtds_percpu == NULL);

	bzero(dstate, sizeof (dtrace_dstate_t));

	if ((dstate->dtds_chunksize = chunksize) == 0)
		dstate->dtds_chunksize = DTRACE_DYNVAR_CHUNKSIZE;

	VERIFY(dstate->dtds_chunksize < (LONG_MAX - sizeof (dtrace_dynhash_t)));

	if (size < (min_size = dstate->dtds_chunksize + sizeof (dtrace_dynhash_t)))
		size = min_size;

	if ((base = kmem_zalloc(size, KM_NOSLEEP)) == NULL)
		return (ENOMEM);

	dstate->dtds_size = size;
	dstate->dtds_base = base;
	dstate->dtds_percpu = kmem_cache_alloc(dtrace_state_cache, KM_SLEEP);
	bzero(dstate->dtds_percpu, (int)NCPU * sizeof (dtrace_dstate_percpu_t));

	hashsize = size / (dstate->dtds_chunksize + sizeof (dtrace_dynhash_t));

	if (hashsize != 1 && (hashsize & 1))
		hashsize--;

	dstate->dtds_hashsize = hashsize;
	dstate->dtds_hash = dstate->dtds_base;

	/*
	 * Set all of our hash buckets to point to the single sink, and (if
	 * it hasn't already been set), set the sink's hash value to be the
	 * sink sentinel value.  The sink is needed for dynamic variable
	 * lookups to know that they have iterated over an entire, valid hash
	 * chain.
	 */
	for (i = 0; i < hashsize; i++)
		dstate->dtds_hash[i].dtdh_chain = &dtrace_dynhash_sink;

	if (dtrace_dynhash_sink.dtdv_hashval != DTRACE_DYNHASH_SINK)
		dtrace_dynhash_sink.dtdv_hashval = DTRACE_DYNHASH_SINK;

	/*
	 * Determine number of active CPUs.  Divide free list evenly among
	 * active CPUs.
	 */
	start = (dtrace_dynvar_t *)
	    ((uintptr_t)base + hashsize * sizeof (dtrace_dynhash_t));
	limit = (uintptr_t)base + size;

	VERIFY((uintptr_t)start < limit);
	VERIFY((uintptr_t)start >= (uintptr_t)base);

	maxper = (limit - (uintptr_t)start) / (int)NCPU;
	maxper = (maxper / dstate->dtds_chunksize) * dstate->dtds_chunksize;

	for (i = 0; i < NCPU; i++) {
		dstate->dtds_percpu[i].dtdsc_free = dvar = start;

		/*
		 * If we don't even have enough chunks to make it once through
		 * NCPUs, we're just going to allocate everything to the first
		 * CPU.  And if we're on the last CPU, we're going to allocate
		 * whatever is left over.  In either case, we set the limit to
		 * be the limit of the dynamic variable space.
		 */
		if (maxper == 0 || i == NCPU - 1) {
			limit = (uintptr_t)base + size;
			start = NULL;
		} else {
			limit = (uintptr_t)start + maxper;
			start = (dtrace_dynvar_t *)limit;
		}

		VERIFY(limit <= (uintptr_t)base + size);

		for (;;) {
			next = (dtrace_dynvar_t *)((uintptr_t)dvar +
			    dstate->dtds_chunksize);

			if ((uintptr_t)next + dstate->dtds_chunksize >= limit)
				break;

			VERIFY((uintptr_t)dvar >= (uintptr_t)base &&
			    (uintptr_t)dvar <= (uintptr_t)base + size);
			dvar->dtdv_next = next;
			dvar = next;
		}

		if (maxper == 0)
			break;
	}

	return (0);
}