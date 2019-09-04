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
struct waitq_link {int dummy; } ;
struct lt_elem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_wqlinktable ; 
 struct lt_elem* ltable_alloc_elem (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wql_do_alloc_stats (struct lt_elem*) ; 

__attribute__((used)) static struct waitq_link *wql_alloc_link(int type)
{
	struct lt_elem *elem;

	elem = ltable_alloc_elem(&g_wqlinktable, type, 1, 0);
	wql_do_alloc_stats(elem);
	return (struct waitq_link *)elem;
}