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
struct pt_regs {unsigned long sp; struct pt_regs* next_frame; } ;

/* Variables and functions */
 scalar_t__ user_mode (struct pt_regs const*) ; 

inline unsigned long user_stack(const struct pt_regs *regs)
{
	while (regs->next_frame)
		regs = regs->next_frame;
	return user_mode(regs) ? regs->sp : 0;
}