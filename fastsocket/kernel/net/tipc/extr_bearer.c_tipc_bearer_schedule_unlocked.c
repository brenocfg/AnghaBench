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
struct link {int /*<<< orphan*/  link_list; } ;
struct bearer {int /*<<< orphan*/  cong_links; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tipc_bearer_schedule_unlocked(struct bearer *b_ptr, struct link *l_ptr)
{
	list_move_tail(&l_ptr->link_list, &b_ptr->cong_links);
}