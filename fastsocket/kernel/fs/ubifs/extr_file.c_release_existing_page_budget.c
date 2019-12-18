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
struct ubifs_info {int /*<<< orphan*/  page_budget; } ;
struct ubifs_budget_req {int /*<<< orphan*/  dd_growth; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 

__attribute__((used)) static void release_existing_page_budget(struct ubifs_info *c)
{
	struct ubifs_budget_req req = { .dd_growth = c->page_budget};

	ubifs_release_budget(c, &req);
}