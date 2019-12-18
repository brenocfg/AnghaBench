#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ thread_t ;
struct callstack {scalar_t__ nframes; unsigned long long* frames; } ;
struct arm_saved_state {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  uesp; } ;
struct TYPE_4__ {int /*<<< orphan*/  rsp; } ;
struct TYPE_5__ {TYPE_1__ isf; } ;

/* Variables and functions */
 scalar_t__ MAX_CALLSTACK_FRAMES ; 
 int PSR_TF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  copyin (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ current_thread () ; 
 int get_saved_state_cpsr (struct arm_saved_state*) ; 
 unsigned long long get_saved_state_lr (struct arm_saved_state*) ; 
 int /*<<< orphan*/  get_task_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_threadtask (scalar_t__) ; 
 void* get_user_regs (scalar_t__) ; 
 int is_saved_state64 (int /*<<< orphan*/ *) ; 
 TYPE_3__* saved_state32 (int /*<<< orphan*/ *) ; 
 TYPE_2__* saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_read_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*,int) ; 

__attribute__((used)) static void
callstack_fixup_user(struct callstack *cs, thread_t thread)
{
	uint64_t fixup_val = 0;
	assert(cs->nframes < MAX_CALLSTACK_FRAMES);

#if defined(__x86_64__)
	user_addr_t sp_user;
	bool user_64;
	x86_saved_state_t *state;

	state = get_user_regs(thread);
	if (!state) {
		goto out;
	}

	user_64 = is_saved_state64(state);
	if (user_64) {
	    sp_user = saved_state64(state)->isf.rsp;
	} else {
		sp_user = saved_state32(state)->uesp;
	}

	if (thread == current_thread()) {
		(void)copyin(sp_user, (char *)&fixup_val,
			user_64 ? sizeof(uint64_t) : sizeof(uint32_t));
	} else {
		(void)vm_map_read_user(get_task_map(get_threadtask(thread)), sp_user,
			&fixup_val, user_64 ? sizeof(uint64_t) : sizeof(uint32_t));
	}

#elif defined(__arm64__) || defined(__arm__)

	struct arm_saved_state *state = get_user_regs(thread);
	if (!state) {
		goto out;
	}

	/* encode thumb mode into low bit of PC */
	if (get_saved_state_cpsr(state) & PSR_TF) {
		cs->frames[0] |= 1ULL;
	}

	fixup_val = get_saved_state_lr(state);

#else
#error "callstack_fixup_user: unsupported architecture"
#endif

out:
	cs->frames[cs->nframes++] = fixup_val;
}