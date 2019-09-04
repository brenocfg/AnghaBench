#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t uint64_t ;
struct TYPE_12__ {int dtds_hashsize; uintptr_t dtds_chunksize; scalar_t__ dtds_base; int /*<<< orphan*/  dtds_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  dtvs_nglobals; int /*<<< orphan*/  dtvs_globals; int /*<<< orphan*/  dtvs_nlocals; int /*<<< orphan*/  dtvs_locals; TYPE_5__ dtvs_dynvars; } ;
typedef  TYPE_2__ dtrace_vstate_t ;
struct TYPE_10__ {uintptr_t dtms_scratch_base; int /*<<< orphan*/  dtms_scratch_size; } ;
typedef  TYPE_3__ dtrace_mstate_t ;
typedef  int /*<<< orphan*/  dtrace_key_t ;
struct TYPE_8__ {int dtt_nkeys; } ;
struct TYPE_11__ {scalar_t__ dtdv_hashval; TYPE_1__ dtdv_tuple; } ;
typedef  TYPE_4__ dtrace_dynvar_t ;
typedef  int /*<<< orphan*/  dtrace_dynhash_t ;
typedef  TYPE_5__ dtrace_dstate_t ;

/* Variables and functions */
 scalar_t__ DTRACE_DYNHASH_FREE ; 
 scalar_t__ DTRACE_INRANGE (uintptr_t,size_t,uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_RANGE_REMAIN (size_t*,uintptr_t,uintptr_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_canstore_statvar (uintptr_t,size_t,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_canstore_remains(uint64_t addr, size_t sz, size_t *remain,
	dtrace_mstate_t *mstate, dtrace_vstate_t *vstate)
{
	/*
	 * First, check to see if the address is in scratch space...
	 */
	if (DTRACE_INRANGE(addr, sz, mstate->dtms_scratch_base,
	    mstate->dtms_scratch_size)) {
		DTRACE_RANGE_REMAIN(remain, addr, mstate->dtms_scratch_base,
			mstate->dtms_scratch_size);
		return (1);
	}
	/*
	 * Now check to see if it's a dynamic variable.  This check will pick
	 * up both thread-local variables and any global dynamically-allocated
	 * variables.
	 */
	if (DTRACE_INRANGE(addr, sz, (uintptr_t)vstate->dtvs_dynvars.dtds_base,
	    vstate->dtvs_dynvars.dtds_size)) {
		dtrace_dstate_t *dstate = &vstate->dtvs_dynvars;
		uintptr_t base = (uintptr_t)dstate->dtds_base +
		    (dstate->dtds_hashsize * sizeof (dtrace_dynhash_t));
		uintptr_t chunkoffs;
		dtrace_dynvar_t *dvar;

		/*
		 * Before we assume that we can store here, we need to make
		 * sure that it isn't in our metadata -- storing to our
		 * dynamic variable metadata would corrupt our state.  For
		 * the range to not include any dynamic variable metadata,
		 * it must:
		 *
		 *	(1) Start above the hash table that is at the base of
		 *	the dynamic variable space
		 *
		 *	(2) Have a starting chunk offset that is beyond the
		 *	dtrace_dynvar_t that is at the base of every chunk
		 *
		 *	(3) Not span a chunk boundary
		 *
		 *	(4) Not be in the tuple space of a dynamic variable
		 *
		 */
		if (addr < base)
			return (0);

		chunkoffs = (addr - base) % dstate->dtds_chunksize;

		if (chunkoffs < sizeof (dtrace_dynvar_t))
			return (0);

		if (chunkoffs + sz > dstate->dtds_chunksize)
			return (0);

		dvar = (dtrace_dynvar_t *)((uintptr_t)addr - chunkoffs);

		if (dvar->dtdv_hashval == DTRACE_DYNHASH_FREE)
			return (0);

		if (chunkoffs < sizeof (dtrace_dynvar_t) +
			((dvar->dtdv_tuple.dtt_nkeys - 1) * sizeof (dtrace_key_t)))
			return (0);

		return (1);
	}

	/*
	 * Finally, check the static local and global variables.  These checks
	 * take the longest, so we perform them last.
	 */
	if (dtrace_canstore_statvar(addr, sz, remain,
	    vstate->dtvs_locals, vstate->dtvs_nlocals))
		return (1);

	if (dtrace_canstore_statvar(addr, sz, remain,
	    vstate->dtvs_globals, vstate->dtvs_nglobals))
		return (1);

	return (0);
}