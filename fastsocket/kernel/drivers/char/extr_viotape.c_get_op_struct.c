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
struct op_struct {int /*<<< orphan*/  com; struct op_struct* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct op_struct*,int /*<<< orphan*/ ,int) ; 
 struct op_struct* op_struct_list ; 
 int /*<<< orphan*/  op_struct_list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct op_struct *get_op_struct(void)
{
	struct op_struct *retval;
	unsigned long flags;

	spin_lock_irqsave(&op_struct_list_lock, flags);
	retval = op_struct_list;
	if (retval)
		op_struct_list = retval->next;
	spin_unlock_irqrestore(&op_struct_list_lock, flags);
	if (retval) {
		memset(retval, 0, sizeof(*retval));
		init_completion(&retval->com);
	}

	return retval;
}