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
typedef  int /*<<< orphan*/  uint64_t ;
struct wq_prepost {int dummy; } ;
struct lt_elem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_prepost_table ; 
 struct lt_elem* lt_elem_list_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqp_do_alloc_stats (struct lt_elem*) ; 

__attribute__((used)) static struct wq_prepost *wq_prepost_rfirst(uint64_t id)
{
	struct lt_elem *elem;
	elem = lt_elem_list_first(&g_prepost_table, id);
	wqp_do_alloc_stats(elem);
	return (struct wq_prepost *)(void *)elem;
}