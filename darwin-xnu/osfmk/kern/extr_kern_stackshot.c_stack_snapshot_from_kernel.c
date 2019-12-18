#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct kcdata_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KCDATA_BUFFER_BEGIN_DELTA_STACKSHOT ; 
 int KCDATA_BUFFER_BEGIN_STACKSHOT ; 
 int KCFLAG_NO_AUTO_ENDBUFFER ; 
 int KCFLAG_USE_MEMCOPY ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_LOCK_OWNED ; 
 scalar_t__ KERN_NOT_SUPPORTED ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  KF_STACKSHOT_OVRD ; 
 int STACKSHOT_COLLECT_DELTA_SNAPSHOT ; 
 int /*<<< orphan*/  STACKSHOT_SUBSYS_LOCK () ; 
 int /*<<< orphan*/  STACKSHOT_SUBSYS_TRY_LOCK () ; 
 int /*<<< orphan*/  STACKSHOT_SUBSYS_UNLOCK () ; 
 int STACKSHOT_TRYLOCK ; 
 scalar_t__ TRUE ; 
 scalar_t__ kcdata_memory_static_init (struct kcdata_descriptor*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  kdp_snapshot_preflight (int,void*,int,int,struct kcdata_descriptor*,int /*<<< orphan*/ ) ; 
 unsigned int kdp_stack_snapshot_bytes_traced () ; 
 scalar_t__ kern_feature_override (int /*<<< orphan*/ ) ; 
 int max_tracebuf_size ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stackshot_kcdata_p ; 
 scalar_t__ stackshot_trap () ; 

kern_return_t
stack_snapshot_from_kernel(int pid, void *buf, uint32_t size, uint32_t flags, uint64_t delta_since_timestamp, unsigned *bytes_traced)
{
	kern_return_t error = KERN_SUCCESS;
	boolean_t istate;

#if DEVELOPMENT || DEBUG
	if (kern_feature_override(KF_STACKSHOT_OVRD) == TRUE) {
		error = KERN_NOT_SUPPORTED;
		goto out;
	}
#endif
	if ((buf == NULL) || (size <= 0) || (bytes_traced == NULL)) {
		return KERN_INVALID_ARGUMENT;
	}

	/* cap in individual stackshot to max_tracebuf_size */
	if (size > max_tracebuf_size) {
		size = max_tracebuf_size;
	}

	/* Serialize tracing */
	if (flags & STACKSHOT_TRYLOCK) {
		if (!STACKSHOT_SUBSYS_TRY_LOCK()) {
			return KERN_LOCK_OWNED;
		}
	} else {
		STACKSHOT_SUBSYS_LOCK();
	}

	struct kcdata_descriptor kcdata;
	uint32_t hdr_tag = (flags & STACKSHOT_COLLECT_DELTA_SNAPSHOT) ?
		KCDATA_BUFFER_BEGIN_DELTA_STACKSHOT : KCDATA_BUFFER_BEGIN_STACKSHOT;

	error = kcdata_memory_static_init(&kcdata, (mach_vm_address_t)buf, hdr_tag, size,
									  KCFLAG_USE_MEMCOPY | KCFLAG_NO_AUTO_ENDBUFFER);
	if (error) {
		goto out;
	}

	istate = ml_set_interrupts_enabled(FALSE);

	/* Preload trace parameters*/
	kdp_snapshot_preflight(pid, buf, size, flags, &kcdata, delta_since_timestamp);

	/*
	 * Trap to the debugger to obtain a coherent stack snapshot; this populates
	 * the trace buffer
	 */
	error = stackshot_trap();

	ml_set_interrupts_enabled(istate);

	*bytes_traced = kdp_stack_snapshot_bytes_traced();

out:
	stackshot_kcdata_p = NULL;
	STACKSHOT_SUBSYS_UNLOCK();
	return error;
}