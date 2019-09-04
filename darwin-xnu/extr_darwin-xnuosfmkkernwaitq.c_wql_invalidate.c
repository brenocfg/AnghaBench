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
struct waitq_link {int /*<<< orphan*/  wqte; } ;

/* Variables and functions */
 int /*<<< orphan*/  lt_elem_invalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wql_do_invalidate_stats (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wql_invalidate(struct waitq_link *link)
{
	lt_elem_invalidate(&link->wqte);
	wql_do_invalidate_stats(&link->wqte);
}