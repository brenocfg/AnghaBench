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
struct procinfo_coalinfo {int /*<<< orphan*/  coalition_tasks; int /*<<< orphan*/  coalition_type; int /*<<< orphan*/  coalition_id; } ;
struct coalition {int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  coalition_get_task_count (struct coalition*) ; 

__attribute__((used)) static void coalition_fill_procinfo(struct coalition *coal,
				    struct procinfo_coalinfo *coalinfo)
{
	coalinfo->coalition_id = coal->id;
	coalinfo->coalition_type = coal->type;
	coalinfo->coalition_tasks = coalition_get_task_count(coal);
}