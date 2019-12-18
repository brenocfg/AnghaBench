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
struct arm_saved_state {int dummy; } ;
typedef  struct arm_saved_state x86_saved_state_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {uintptr_t eip; uintptr_t ebp; } ;
struct TYPE_4__ {uintptr_t rip; } ;
struct TYPE_5__ {uintptr_t rbp; TYPE_1__ isf; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INVALID_USER_FP (uintptr_t) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int copyin (scalar_t__,char*,size_t) ; 
 void* current_thread () ; 
 uintptr_t get_saved_state_fp (struct arm_saved_state*) ; 
 uintptr_t get_saved_state_pc (struct arm_saved_state*) ; 
 int /*<<< orphan*/ * get_task_map_reference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_threadtask (void*) ; 
 struct arm_saved_state* get_user_regs (void*) ; 
 int is_saved_state64 (struct arm_saved_state*) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 TYPE_3__* saved_state32 (struct arm_saved_state*) ; 
 TYPE_2__* saved_state64 (struct arm_saved_state*) ; 
 int /*<<< orphan*/  vm_map_deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_map_switch (int /*<<< orphan*/ *) ; 

int
backtrace_thread_user(void *thread, uintptr_t *bt, uint32_t max_frames,
	uint32_t *frames_out, bool *user_64_out)
{
	bool user_64;
	uintptr_t pc, fp, next_fp;
	vm_map_t map = NULL, old_map = NULL;
	uint32_t frame_index = 0;
	int err = 0;
	size_t frame_size;

	assert(bt != NULL);
	assert(max_frames > 0);
	assert(frames_out != NULL);
	assert(user_64_out != NULL);

#if defined(__x86_64__)

	/* don't allow a malformed user stack to copyin arbitrary kernel data */
#define INVALID_USER_FP(FP) ((FP) == 0 || !IS_USERADDR64_CANONICAL((FP)))

	x86_saved_state_t *state = get_user_regs(thread);

	if (!state) {
		return EINVAL;
	}

	user_64 = is_saved_state64(state);
	if (user_64) {
		pc = saved_state64(state)->isf.rip;
		fp = saved_state64(state)->rbp;
	} else {
		pc = saved_state32(state)->eip;
		fp = saved_state32(state)->ebp;
	}

#elif defined(__arm64__)

	/* ARM expects stack frames to be aligned to 16 bytes */
#define INVALID_USER_FP(FP) ((FP) == 0 || ((FP) & 0x3UL) != 0UL)

	struct arm_saved_state *state = get_user_regs(thread);
	if (!state) {
		return EINVAL;
	}

	user_64 = is_saved_state64(state);
	pc = get_saved_state_pc(state);
	fp = get_saved_state_fp(state);

#elif defined(__arm__)

	/* ARM expects stack frames to be aligned to 16 bytes */
#define INVALID_USER_FP(FP) ((FP) == 0 || ((FP) & 0x3UL) != 0UL)

	struct arm_saved_state *state = get_user_regs(thread);
	if (!state) {
		return EINVAL;
	}

	user_64 = false;
	pc = get_saved_state_pc(state);
	fp = get_saved_state_fp(state);

#else /* defined(__arm__) */
#error "backtrace_thread_user: unsupported architecture"
#endif /* !defined(__arm__) */

	if (max_frames == 0) {
		goto out;
	}

	bt[frame_index++] = pc;

	if (frame_index >= max_frames) {
		goto out;
	}

	if (INVALID_USER_FP(fp)) {
		goto out;
	}

	assert(ml_get_interrupts_enabled() == TRUE);
	if (!ml_get_interrupts_enabled()) {
		return EINVAL;
	}

	union {
		struct {
			uint64_t fp;
			uint64_t ret;
		} u64;
		struct {
			uint32_t fp;
			uint32_t ret;
		} u32;
	} frame;

	frame_size = 2 * (user_64 ? sizeof(uint64_t) : sizeof(uint32_t));

	/* switch to the correct map, for copyin */
	if (thread != current_thread()) {
		map = get_task_map_reference(get_threadtask(thread));
		if (map == NULL) {
			return EINVAL;
		}
		old_map = vm_map_switch(map);
	} else {
		map = NULL;
	}

	while (fp != 0 && frame_index < max_frames) {
		err = copyin(fp, (char *)&frame, frame_size);
		if (err) {
			goto out;
		}

		next_fp = user_64 ? frame.u64.fp : frame.u32.fp;

		if (INVALID_USER_FP(next_fp)) {
			break;
		}

		uintptr_t ret_addr = user_64 ? frame.u64.ret : frame.u32.ret;
		bt[frame_index++] = ret_addr;

		/* stacks grow down; backtracing should be moving to higher addresses */
		if (next_fp <= fp) {
			break;
		}
		fp = next_fp;
	}

out:
	if (map) {
		(void)vm_map_switch(old_map);
		vm_map_deallocate(map);
	}

	*user_64_out = user_64;
	*frames_out = frame_index;
	return err;
#undef INVALID_USER_FP
}