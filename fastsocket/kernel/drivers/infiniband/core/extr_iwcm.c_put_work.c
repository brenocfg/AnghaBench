#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iwcm_work {TYPE_1__* cm_id; int /*<<< orphan*/  free_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  work_free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_work(struct iwcm_work *work)
{
	list_add(&work->free_list, &work->cm_id->work_free_list);
}