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
typedef  int /*<<< orphan*/  dis86_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_imm_opnd (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void
dtrace_disp_opnd(dis86_t *x, int wbit, int size, int opindex)
{
	dtrace_imm_opnd(x, wbit, size, opindex);
#ifdef DIS_TEXT
	x->d86_opnd[opindex].d86_mode = MODE_IPREL;
#endif
}