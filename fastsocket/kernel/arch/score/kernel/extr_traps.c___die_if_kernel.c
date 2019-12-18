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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __die (char const*,struct pt_regs*,char const*,char const*,unsigned long) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void __die_if_kernel(const char *str, struct pt_regs *regs,
		const char *file, const char *func, unsigned long line)
{
	if (!user_mode(regs))
		__die(str, regs, file, func, line);
}