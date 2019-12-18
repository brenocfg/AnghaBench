#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int const uint32_t ;
typedef  size_t processorid_t ;
struct TYPE_15__ {TYPE_1__** dts_ecbs; scalar_t__ dts_necbs; TYPE_5__* dts_buffer; TYPE_3__* dts_speculations; scalar_t__ dts_nspeculations; } ;
typedef  TYPE_2__ dtrace_state_t ;
struct TYPE_16__ {int dtsp_state; TYPE_5__* dtsp_buffer; } ;
typedef  TYPE_3__ dtrace_speculation_t ;
typedef  int dtrace_speculation_state_t ;
typedef  int dtrace_specid_t ;
struct TYPE_17__ {int dtrh_epid; } ;
typedef  TYPE_4__ dtrace_rechdr_t ;
typedef  int dtrace_epid_t ;
struct TYPE_18__ {uintptr_t dtb_offset; scalar_t__ dtb_drops; int /*<<< orphan*/  dtb_xamot_drops; scalar_t__ dtb_tomax; } ;
typedef  TYPE_5__ dtrace_buffer_t ;
struct TYPE_14__ {size_t dte_size; } ;
struct TYPE_13__ {int /*<<< orphan*/  cpuc_dtrace_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
#define  DTRACESPEC_ACTIVE 133 
#define  DTRACESPEC_ACTIVEMANY 132 
#define  DTRACESPEC_ACTIVEONE 131 
#define  DTRACESPEC_COMMITTING 130 
 int DTRACESPEC_COMMITTINGMANY ; 
#define  DTRACESPEC_DISCARDING 129 
#define  DTRACESPEC_INACTIVE 128 
 int DTRACE_EPIDNONE ; 
 scalar_t__ DTRACE_RECORD_LOAD_TIMESTAMP (TYPE_4__*) ; 
 int /*<<< orphan*/  DTRACE_RECORD_STORE_TIMESTAMP (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ UINT64_MAX ; 
 TYPE_10__* cpu_core ; 
 int /*<<< orphan*/  dtrace_buffer_drop (TYPE_5__*) ; 
 intptr_t dtrace_buffer_reserve (TYPE_5__*,uintptr_t,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int dtrace_cas32 (int const*,int const,int) ; 
 int /*<<< orphan*/  dtrace_gethrtime () ; 

__attribute__((used)) static void
dtrace_speculation_commit(dtrace_state_t *state, processorid_t cpu,
    dtrace_specid_t which)
{
	dtrace_speculation_t *spec;
	dtrace_buffer_t *src, *dest;
	uintptr_t daddr, saddr, dlimit, slimit;
	dtrace_speculation_state_t current,  new = DTRACESPEC_INACTIVE;
	intptr_t offs;
	uint64_t timestamp;

	if (which == 0)
		return;

	if (which > (dtrace_specid_t)state->dts_nspeculations) {
		cpu_core[cpu].cpuc_dtrace_flags |= CPU_DTRACE_ILLOP;
		return;
	}
	
	spec = &state->dts_speculations[which - 1];
	src = &spec->dtsp_buffer[cpu];
	dest = &state->dts_buffer[cpu];

	do {
		current = spec->dtsp_state;

		if (current == DTRACESPEC_COMMITTINGMANY)
			break;

		switch (current) {
		case DTRACESPEC_INACTIVE:
		case DTRACESPEC_DISCARDING:
			return;

		case DTRACESPEC_COMMITTING:
			/*
			 * This is only possible if we are (a) commit()'ing
			 * without having done a prior speculate() on this CPU
			 * and (b) racing with another commit() on a different
			 * CPU.  There's nothing to do -- we just assert that
			 * our offset is 0.
			 */
			ASSERT(src->dtb_offset == 0);
			return;

		case DTRACESPEC_ACTIVE:
			new = DTRACESPEC_COMMITTING;
			break;

		case DTRACESPEC_ACTIVEONE:
			/*
			 * This speculation is active on one CPU.  If our
			 * buffer offset is non-zero, we know that the one CPU
			 * must be us.  Otherwise, we are committing on a
			 * different CPU from the speculate(), and we must
			 * rely on being asynchronously cleaned.
			 */
			if (src->dtb_offset != 0) {
				new = DTRACESPEC_COMMITTING;
				break;
			}
			/*FALLTHROUGH*/

		case DTRACESPEC_ACTIVEMANY:
			new = DTRACESPEC_COMMITTINGMANY;
			break;

		default:
			ASSERT(0);
		}
	} while (dtrace_cas32((uint32_t *)&spec->dtsp_state,
	    current, new) != current);

	/*
	 * We have set the state to indicate that we are committing this
	 * speculation.  Now reserve the necessary space in the destination
	 * buffer.
	 */
	if ((offs = dtrace_buffer_reserve(dest, src->dtb_offset,
	    sizeof (uint64_t), state, NULL)) < 0) {
		dtrace_buffer_drop(dest);
		goto out;
	}

	/*
	 * We have sufficient space to copy the speculative buffer into the
	 * primary buffer.  First, modify the speculative buffer, filling
	 * in the timestamp of all entries with the current time.  The data
	 * must have the commit() time rather than the time it was traced,
	 * so that all entries in the primary buffer are in timestamp order.
	 */
	timestamp = dtrace_gethrtime();
	saddr = (uintptr_t)src->dtb_tomax;
	slimit = saddr + src->dtb_offset;
	while (saddr < slimit) {
		size_t size;
		dtrace_rechdr_t *dtrh = (dtrace_rechdr_t *)saddr;

		if (dtrh->dtrh_epid == DTRACE_EPIDNONE) {
			saddr += sizeof (dtrace_epid_t);
			continue;
		}

		ASSERT(dtrh->dtrh_epid <= ((dtrace_epid_t) state->dts_necbs));
		size = state->dts_ecbs[dtrh->dtrh_epid - 1]->dte_size;

		ASSERT(saddr + size <= slimit);
		ASSERT(size >= sizeof(dtrace_rechdr_t));
		ASSERT(DTRACE_RECORD_LOAD_TIMESTAMP(dtrh) == UINT64_MAX);

		DTRACE_RECORD_STORE_TIMESTAMP(dtrh, timestamp);

		saddr += size;
	}

	/*
	 * Copy the buffer across.  (Note that this is a
	 * highly subobtimal bcopy(); in the unlikely event that this becomes
	 * a serious performance issue, a high-performance DTrace-specific
	 * bcopy() should obviously be invented.)
	 */
	daddr = (uintptr_t)dest->dtb_tomax + offs;
	dlimit = daddr + src->dtb_offset;
	saddr = (uintptr_t)src->dtb_tomax;

	/*
	 * First, the aligned portion.
	 */
	while (dlimit - daddr >= sizeof (uint64_t)) {
		*((uint64_t *)daddr) = *((uint64_t *)saddr);

		daddr += sizeof (uint64_t);
		saddr += sizeof (uint64_t);
	}

	/*
	 * Now any left-over bit...
	 */
	while (dlimit - daddr)
		*((uint8_t *)daddr++) = *((uint8_t *)saddr++);

	/*
	 * Finally, commit the reserved space in the destination buffer.
	 */
	dest->dtb_offset = offs + src->dtb_offset;

out:
	/*
	 * If we're lucky enough to be the only active CPU on this speculation
	 * buffer, we can just set the state back to DTRACESPEC_INACTIVE.
	 */
	if (current == DTRACESPEC_ACTIVE ||
	    (current == DTRACESPEC_ACTIVEONE && new == DTRACESPEC_COMMITTING)) {
		uint32_t rval = dtrace_cas32((uint32_t *)&spec->dtsp_state,
		    DTRACESPEC_COMMITTING, DTRACESPEC_INACTIVE);
#pragma unused(rval) /* __APPLE__ */

		ASSERT(rval == DTRACESPEC_COMMITTING);
	}

	src->dtb_offset = 0;
	src->dtb_xamot_drops += src->dtb_drops;
	src->dtb_drops = 0;
}