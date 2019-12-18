#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ refcnt; } ;
typedef  TYPE_1__ mtrr_var_range_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int addr64_t ;
struct TYPE_6__ {int MTRRcap; unsigned int var_count; TYPE_1__* var_range; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int IA32_MTRRCAP_WC ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_NOT_SUPPORTED ; 
 int /*<<< orphan*/  KERN_NO_SPACE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int LSB (int) ; 
 int /*<<< orphan*/  MTRR_LOCK () ; 
 int /*<<< orphan*/  MTRR_TYPE_UNCACHEABLE ; 
 int /*<<< orphan*/  MTRR_TYPE_WRITEBACK ; 
 int /*<<< orphan*/  MTRR_TYPE_WRITECOMBINE ; 
 int /*<<< orphan*/  MTRR_TYPE_WRITEPROTECT ; 
 int /*<<< orphan*/  MTRR_TYPE_WRITETHROUGH ; 
 int /*<<< orphan*/  MTRR_UNLOCK () ; 
 int /*<<< orphan*/  mp_rendezvous (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mtrr_initialized ; 
 int /*<<< orphan*/  mtrr_msr_dump () ; 
 TYPE_4__ mtrr_state ; 
 int /*<<< orphan*/  mtrr_update_action ; 
 int /*<<< orphan*/  mtrr_update_setup ; 
 int /*<<< orphan*/  mtrr_update_teardown ; 
 int /*<<< orphan*/  var_range_encode (TYPE_1__*,int,int,int /*<<< orphan*/ ,int) ; 
 int var_range_overlap (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

kern_return_t
mtrr_range_add(addr64_t address, uint64_t length, uint32_t type)
{
	mtrr_var_range_t * vr;
	mtrr_var_range_t * free_range;
	kern_return_t      ret = KERN_NO_SPACE;
	int                overlap;
	unsigned int       i;

	DBG("mtrr_range_add base = 0x%llx, size = 0x%llx, type = %d\n",
            address, length, type);

	if (mtrr_initialized == FALSE) {
		return KERN_NOT_SUPPORTED;
	}

	/* check memory type (GPF exception for undefined types) */
	if ((type != MTRR_TYPE_UNCACHEABLE)  &&
	    (type != MTRR_TYPE_WRITECOMBINE) &&
	    (type != MTRR_TYPE_WRITETHROUGH) &&
	    (type != MTRR_TYPE_WRITEPROTECT) &&
	    (type != MTRR_TYPE_WRITEBACK)) {
		return KERN_INVALID_ARGUMENT;
	}

	/* check WC support if requested */
	if ((type == MTRR_TYPE_WRITECOMBINE) &&
	    (mtrr_state.MTRRcap & IA32_MTRRCAP_WC) == 0) {
		return KERN_NOT_SUPPORTED;
	}

	/* leave the fix range area below 1MB alone */
	if (address < 0x100000 || mtrr_state.var_count == 0) {
		return KERN_NOT_SUPPORTED;
	}

	/*
	 * Length must be a power of 2 given by 2^n, where n >= 12.
	 * Base address alignment must be larger than or equal to length.
	 */
	if ((length < 0x1000)       ||
	    (LSB(length) != length) ||
            (address && (length > LSB(address)))) {
		return KERN_INVALID_ARGUMENT;
	}

	MTRR_LOCK();

	/*
	 * Check for overlap and locate a free range.
	 */
	for (i = 0, free_range = NULL; i < mtrr_state.var_count; i++)
	{
		vr = &mtrr_state.var_range[i];

		if (vr->refcnt == 0) {
			/* free range candidate if no overlaps are found */
			free_range = vr;
			continue;
		}

		overlap = var_range_overlap(vr, address, length, type);
		if (overlap > 0) {
			/*
			 * identical overlap permitted, increment ref count.
			 * no hardware update required.
			 */
			free_range = vr;
			break;
		}
		if (overlap < 0) {
			/* unsupported overlapping of memory types */
			free_range = NULL;
			break;
		}
	}

	if (free_range) {
		if (free_range->refcnt++ == 0) {
			var_range_encode(free_range, address, length, type, 1);
			mp_rendezvous(mtrr_update_setup,
				      mtrr_update_action,
				      mtrr_update_teardown, NULL);
		}
		ret = KERN_SUCCESS;
	}

#if MTRR_DEBUG
	mtrr_msr_dump();
#endif

	MTRR_UNLOCK();

	return ret;
}