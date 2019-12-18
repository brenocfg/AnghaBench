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
struct unwind_frame_info {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  unwind_frame_init (struct unwind_frame_info*,int /*<<< orphan*/ ,struct pt_regs*) ; 

void unwind_frame_init_running(struct unwind_frame_info *info, struct pt_regs *regs)
{
	unwind_frame_init(info, current, regs);
}