#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct unw_frame_info {TYPE_4__* sw; } ;
struct TYPE_5__ {int fsr; } ;
struct task_struct {TYPE_1__ thread; } ;
struct TYPE_6__ {int /*<<< orphan*/  ubuf; int /*<<< orphan*/  kbuf; } ;
struct TYPE_7__ {TYPE_2__ set; } ;
struct regset_getset {scalar_t__ count; int pos; TYPE_3__ u; void* ret; struct task_struct* target; } ;
struct pt_regs {int dummy; } ;
struct TYPE_8__ {char f16; } ;

/* Variables and functions */
 int OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access_fpreg_ia32 (int,char*,struct pt_regs*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/ * padding ; 
 int /*<<< orphan*/  setfpxreg (struct task_struct*,int,int,char*) ; 
 int /*<<< orphan*/ * st_space ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 scalar_t__ unw_unwind_to_user (struct unw_frame_info*) ; 
 void* user_regset_copyin (int*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/ * xmm_space ; 

__attribute__((used)) static void do_fpxregs_set(struct unw_frame_info *info, void *arg)
{
	struct regset_getset *dst = arg;
	struct task_struct *task = dst->target;
	char buf[128];
	int start, end;

	if (dst->count == 0 || unw_unwind_to_user(info) < 0)
		return;

	if (dst->pos < OFFSET(st_space[0])) {
		start = dst->pos;
		dst->ret = user_regset_copyin(&dst->pos, &dst->count,
				&dst->u.set.kbuf, &dst->u.set.ubuf,
				buf, 0, OFFSET(st_space[0]));
		if (dst->ret)
			return;
		setfpxreg(task, start, dst->pos, buf);
		if (dst->count == 0)
			return;
	}
	if (dst->pos < OFFSET(xmm_space[0])) {
		struct pt_regs *pt;
		int tos;
		pt = task_pt_regs(task);
		tos = (task->thread.fsr >> 11) & 7;
		start = (dst->pos - OFFSET(st_space[0])) / 16;
		dst->ret = user_regset_copyin(&dst->pos, &dst->count,
				&dst->u.set.kbuf, &dst->u.set.ubuf,
				buf, OFFSET(st_space[0]), OFFSET(xmm_space[0]));
		if (dst->ret)
			return;
		end = (dst->pos - OFFSET(st_space[0])) / 16;
		for (; start < end; start++)
			access_fpreg_ia32(start, buf + 16 * start, pt, info->sw,
						 tos, 1);
		if (dst->count == 0)
			return;
	}
	if (dst->pos < OFFSET(padding[0]))
		dst->ret = user_regset_copyin(&dst->pos, &dst->count,
				&dst->u.set.kbuf, &dst->u.set.ubuf,
				&info->sw->f16, OFFSET(xmm_space[0]),
				 OFFSET(padding[0]));
}