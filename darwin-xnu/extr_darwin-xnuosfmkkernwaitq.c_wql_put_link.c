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
 int /*<<< orphan*/  ltable_put_elem (int /*<<< orphan*/ *,struct lt_elem*) ; 

__attribute__((used)) static void wql_put_link(struct waitq_link *link)
{
	if (!link)
		return;
	ltable_put_elem(&g_wqlinktable, (struct lt_elem *)link);
}