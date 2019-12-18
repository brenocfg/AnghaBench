#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_14__ {struct TYPE_14__* next_in_die; int /*<<< orphan*/ ** caches; TYPE_2__* die; struct TYPE_14__* next_in_core; TYPE_4__* core; } ;
typedef  TYPE_1__ x86_lcpu_t ;
struct TYPE_15__ {TYPE_1__* lcpus; } ;
typedef  TYPE_2__ x86_die_t ;
struct TYPE_16__ {size_t level; int maxcpus; struct TYPE_16__* next; } ;
typedef  TYPE_3__ x86_cpu_cache_t ;
struct TYPE_17__ {TYPE_1__* lcpus; } ;
typedef  TYPE_4__ x86_core_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_13__ {size_t LLCDepth; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 TYPE_12__ topoParms ; 
 int /*<<< orphan*/  x86_cache_add_lcpu (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  x86_cache_free (TYPE_3__*) ; 
 TYPE_3__* x86_cache_list () ; 
 TYPE_3__* x86_match_cache (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  x86_topo_lock ; 

__attribute__((used)) static void
x86_lcpu_add_caches(x86_lcpu_t *lcpu)
{
    x86_cpu_cache_t	*list;
    x86_cpu_cache_t	*cur;
    x86_cpu_cache_t	*match;
    x86_die_t		*die;
    x86_core_t		*core;
    x86_lcpu_t		*cur_lcpu;
    uint32_t		level;
    boolean_t		found		= FALSE;

    assert(lcpu != NULL);

    /*
     * Add the cache data to the topology.
     */
    list = x86_cache_list();

    mp_safe_spin_lock(&x86_topo_lock);

    while (list != NULL) {
	/*
	 * Remove the cache from the front of the list.
	 */
	cur = list;
	list = cur->next;
	cur->next = NULL;
	level = cur->level - 1;

	/*
	 * If the cache isn't shared then just put it where it
	 * belongs.
	 */
	if (cur->maxcpus == 1) {
	    x86_cache_add_lcpu(cur, lcpu);
	    continue;
	}

	/*
	 * We'll assume that all of the caches at a particular level
	 * have the same sharing.  So if we have a cache already at
	 * this level, we'll just skip looking for the match.
	 */
	if (lcpu->caches[level] != NULL) {
	    x86_cache_free(cur);
	    continue;
	}

	/*
	 * This is a shared cache, so we have to figure out if
	 * this is the first time we've seen this cache.  We do
	 * this by searching through the topology and seeing if
	 * this cache is already described.
	 *
	 * Assume that L{LLC-1} are all at the core level and that
	 * LLC is shared at the die level.
	 */
	if (level < topoParms.LLCDepth) {
	    /*
	     * Shared at the core.
	     */
	    core = lcpu->core;
	    cur_lcpu = core->lcpus;
	    while (cur_lcpu != NULL) {
		/*
		 * Skip ourselves.
		 */
		if (cur_lcpu == lcpu) {
		    cur_lcpu = cur_lcpu->next_in_core;
		    continue;
		}

		/*
		 * If there's a cache on this logical CPU,
		 * then use that one.
		 */
		match = x86_match_cache(cur_lcpu->caches[level], cur);
		if (match != NULL) {
		    x86_cache_free(cur);
		    x86_cache_add_lcpu(match, lcpu);
		    found = TRUE;
		    break;
		}

		cur_lcpu = cur_lcpu->next_in_core;
	    }
	} else {
	    /*
	     * Shared at the die.
	     */
	    die = lcpu->die;
	    cur_lcpu = die->lcpus;
	    while (cur_lcpu != NULL) {
		/*
		 * Skip ourselves.
		 */
		if (cur_lcpu == lcpu) {
		    cur_lcpu = cur_lcpu->next_in_die;
		    continue;
		}

		/*
		 * If there's a cache on this logical CPU,
		 * then use that one.
		 */
		match = x86_match_cache(cur_lcpu->caches[level], cur);
		if (match != NULL) {
		    x86_cache_free(cur);
		    x86_cache_add_lcpu(match, lcpu);
		    found = TRUE;
		    break;
		}

		cur_lcpu = cur_lcpu->next_in_die;
	    }
	}

	/*
	 * If a shared cache wasn't found, then this logical CPU must
	 * be the first one encountered.
	 */
	if (!found) {
	    x86_cache_add_lcpu(cur, lcpu);
	}
    }

    simple_unlock(&x86_topo_lock);
}