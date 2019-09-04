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
struct waitq_link {int dummy; } ;
struct lt_elem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_wqlinktable ; 
 struct lt_elem* lt_elem_list_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltable_realloc_elem (int /*<<< orphan*/ *,struct lt_elem*,int) ; 

__attribute__((used)) static struct waitq_link *wql_get_reserved(uint64_t setid, int type)
{
	struct lt_elem *elem;

	elem = lt_elem_list_first(&g_wqlinktable, setid);
	if (!elem)
		return NULL;
	ltable_realloc_elem(&g_wqlinktable, elem, type);
	return (struct waitq_link *)elem;
}