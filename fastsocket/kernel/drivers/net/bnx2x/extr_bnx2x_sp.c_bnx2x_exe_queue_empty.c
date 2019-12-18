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
struct bnx2x_exe_queue_obj {int /*<<< orphan*/  pending_comp; int /*<<< orphan*/  exe_queue; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline bool bnx2x_exe_queue_empty(struct bnx2x_exe_queue_obj *o)
{
	bool empty = list_empty(&o->exe_queue);

	/* Don't reorder!!! */
	mb();

	return empty && list_empty(&o->pending_comp);
}