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
 int /*<<< orphan*/  TRAP (struct pt_regs*) ; 
 int /*<<< orphan*/  computeSignal (int /*<<< orphan*/ ) ; 
 scalar_t__ kgdb_handle_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pt_regs*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int kgdb_iabr_match(struct pt_regs *regs)
{
	if (user_mode(regs))
		return 0;

	if (kgdb_handle_exception(0, computeSignal(TRAP(regs)), 0, regs) != 0)
		return 0;
	return 1;
}