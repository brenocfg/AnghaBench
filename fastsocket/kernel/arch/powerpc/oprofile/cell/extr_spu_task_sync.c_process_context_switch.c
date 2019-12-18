#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spu {unsigned int number; unsigned int pid; unsigned int tgid; } ;
struct TYPE_2__ {int ctx_sw_seen; } ;

/* Variables and functions */
 int ENOENT ; 
 unsigned int ESCAPE_CODE ; 
 unsigned int SPU_CTX_SWITCH_CODE ; 
 int /*<<< orphan*/  buffer_lock ; 
 unsigned long get_exec_dcookie_and_offset (struct spu*,unsigned int*,unsigned long*,unsigned long) ; 
 int prepare_cached_spu_info (struct spu*,unsigned long) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* spu_buff ; 
 int /*<<< orphan*/  spu_buff_add (unsigned int,unsigned int) ; 

__attribute__((used)) static int process_context_switch(struct spu *spu, unsigned long objectId)
{
	unsigned long flags;
	int retval;
	unsigned int offset = 0;
	unsigned long spu_cookie = 0, app_dcookie;

	retval = prepare_cached_spu_info(spu, objectId);
	if (retval)
		goto out;

	/* Get dcookie first because a mutex_lock is taken in that
	 * code path, so interrupts must not be disabled.
	 */
	app_dcookie = get_exec_dcookie_and_offset(spu, &offset, &spu_cookie, objectId);
	if (!app_dcookie || !spu_cookie) {
		retval  = -ENOENT;
		goto out;
	}

	/* Record context info in event buffer */
	spin_lock_irqsave(&buffer_lock, flags);
	spu_buff_add(ESCAPE_CODE, spu->number);
	spu_buff_add(SPU_CTX_SWITCH_CODE, spu->number);
	spu_buff_add(spu->number, spu->number);
	spu_buff_add(spu->pid, spu->number);
	spu_buff_add(spu->tgid, spu->number);
	spu_buff_add(app_dcookie, spu->number);
	spu_buff_add(spu_cookie, spu->number);
	spu_buff_add(offset, spu->number);

	/* Set flag to indicate SPU PC data can now be written out.  If
	 * the SPU program counter data is seen before an SPU context
	 * record is seen, the postprocessing will fail.
	 */
	spu_buff[spu->number].ctx_sw_seen = 1;

	spin_unlock_irqrestore(&buffer_lock, flags);
	smp_wmb();	/* insure spu event buffer updates are written */
			/* don't want entries intermingled... */
out:
	return retval;
}