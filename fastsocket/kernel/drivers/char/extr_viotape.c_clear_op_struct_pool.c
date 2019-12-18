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
 int /*<<< orphan*/  kfree (struct op_struct*) ; 
 struct op_struct* op_struct_list ; 

__attribute__((used)) static void clear_op_struct_pool(void)
{
	while (op_struct_list) {
		struct op_struct *toFree = op_struct_list;
		op_struct_list = op_struct_list->next;
		kfree(toFree);
	}
}