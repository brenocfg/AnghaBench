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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_CCR ; 
 unsigned char* condmask ; 
 unsigned char h8300_get_reg (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isbranch(struct task_struct *task,int reson)
{
	unsigned char cond = h8300_get_reg(task, PT_CCR);
	/* encode complex conditions */
	/* B4: N^V
	   B5: Z|(N^V)
	   B6: C|Z */
	__asm__("bld #3,%w0\n\t"
		"bxor #1,%w0\n\t"
		"bst #4,%w0\n\t"
		"bor #2,%w0\n\t"
		"bst #5,%w0\n\t"
		"bld #2,%w0\n\t"
		"bor #0,%w0\n\t"
		"bst #6,%w0\n\t"
		:"=&r"(cond)::"cc");
	cond &= condmask[reson >> 1];
	if (!(reson & 1))
		return cond == 0;
	else
		return cond != 0;
}