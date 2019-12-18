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
struct pt_regs {int pc; int npc; } ;

/* Variables and functions */

__attribute__((used)) static inline void advance(struct pt_regs *regs)
{
	regs->pc   = regs->npc;
	regs->npc += 4;
}