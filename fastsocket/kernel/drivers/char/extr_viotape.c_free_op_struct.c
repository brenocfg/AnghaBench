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
struct op_struct {struct op_struct* next; } ;

/* Variables and functions */
 struct op_struct* op_struct_list ; 
 int /*<<< orphan*/  op_struct_list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_op_struct(struct op_struct *op_struct)
{
	unsigned long flags;

	spin_lock_irqsave(&op_struct_list_lock, flags);
	op_struct->next = op_struct_list;
	op_struct_list = op_struct;
	spin_unlock_irqrestore(&op_struct_list_lock, flags);
}