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
 int /*<<< orphan*/  PT_PSW ; 
 int get_stack_long (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
check_condition_bit(struct task_struct *child)
{
	return (int)((get_stack_long(child, PT_PSW) >> 8) & 1);
}